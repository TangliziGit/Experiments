package library;

import java.util.*;
import java.sql.*;
import java.text.*;

/**
 * class Library represents the functionality of a library
 * 
 * @author iCarnegie
 * @version 1.0
 */
public class Library {
    // singleton DBWrapper
    private DBWrapper myConnection = null;

    /**
     * class Library constructor
     */
    public Library() throws Exception {

	myConnection = DBWrapper.Instance();
    }

    /**
     * holdBook places a hold on book with given call number for the given
     * member
     * 
     * @param callNumber
     *            String call number of book to hold
     * @param member
     *            Member member who wishes to hold the book.
     * @return boolean
     */
    public boolean holdBook(String callNumber, Member member) throws Exception {

	String sqlQuery = "select count(*) as counted from hold where callnumber='"
		+ callNumber + "' and ssn='" + member.getSSN() + "'";
	boolean alreadyHeld = false;
	ResultSet r = null;
	// Select the count of the books. If it is 1, this book is already held.
	r = myConnection.runQuery(sqlQuery);
	if (r.next()) {
	    if (r.getInt("counted") == 1) {
		alreadyHeld = true;
	    }
	}
	// if alreadyHeld is true, then don't place a hold. Place a hold
	// otherwise.
	if (alreadyHeld) {
	    return true;
	} else {
	    sqlQuery = "INSERT INTO Hold VALUES (" + member.getSSN() + ", '"
		    + callNumber + "', CURRENT_TIMESTAMP)";
	    if (myConnection.runUpdate(sqlQuery) > 0)
		return true;
	    else
		return false;

	}
    }

    /**
     * checkinBook checks the book with the specified book id into the library.
     * 
     * @param bookId
     *            int id of book to check in
     * @return boolean
     */
    public boolean checkInBook(int bookId) throws Exception {

	// Build the sql query.
	String sqlQuery = "UPDATE Book SET borrowerssn = null, librarianssn = null, duedate = null WHERE BookID = "
		+ bookId;
	// Run the update.
	if (myConnection.runUpdate(sqlQuery) > 0)
	    return true;
	else
	    return false;
    }

    /**
     * approve a check out for book with given book id for a member with given
     * member ssn
     * 
     * @param bookId
     *            int id of book to check out
     * @param memberSSN
     *            int ssn of member who wants to check book out
     * @return boolean
     */
    private boolean approveCheckout(int bookId, int memberSSN) throws Exception {

	boolean canCheckOut = true;

	// check to see if that book is already checked out
	boolean checkedOut = LibraryBook.isCheckedOut(bookId);

	if (checkedOut) {
	    canCheckOut = false;
	} else {
	    // see if another member has higher priority on this book

	    // We have to check the holds, if the number of
	    // holds on this title exceeds the number of
	    // available copies.

	    String callNumber = LibraryBook.getBook(bookId).getCallNumber();
	    int availableCopyCount = LibraryBookTitle
		    .getAvailableTitleCopyCount(callNumber);
	    int heldCopyCount = LibraryBookTitle.getTitleHoldCount(callNumber);

	    String MemberSSN = new String("" + memberSSN);
	    HoldSet holds = LibraryBookTitle.getTitleHolds(callNumber);
	    heldCopyCount = holds.getHoldCount();

	    if ((heldCopyCount > 0) && (availableCopyCount < heldCopyCount)) {
		int i = 0;
		boolean highEnoughPriority = false;
		while ((i < holds.getHoldCount()) && (i < availableCopyCount)) {
		    if (holds.getHoldAt(i).getHolderSSN().equals(MemberSSN)) {
			canCheckOut = true;
			break;
		    }
		    i++;
		}
	    }
	}
	return canCheckOut;
    }

    /**
     * checkMemberHold checks in the member with ssn memberSSN has a hold on
     * book with id bookId
     * 
     * @param bookId
     *            int id of book
     * @param memberSSN
     *            int ssn of member
     * @return boolean
     */
    private boolean checkMemberHold(int bookId, int memberSSN) throws Exception {
	boolean isHeld = false;

	Member member = LibraryMember.getMember(memberSSN);
	HoldSet holds = LibraryMember.getMemberHolds(member);
	String callNumber = LibraryBook.getBook(bookId).getCallNumber();

	for (int i = 0; i < holds.getHoldCount(); i++) {
	    if (callNumber.equals(holds.getHoldAt(i).getCallNumber())) {
		isHeld = true;
		break;
	    }
	}
	return isHeld;
    }

    /**
     * checkOutBook checks out the book with bookId for the member with ssn
     * memberSSN by the Librarian librarian
     * 
     * @param bookId
     *            int id of book
     * @param memberSSN
     *            int ssn of member
     * @param librarian
     *            Librarian librarian who is checking this book out
     * @return boolean
     */
    public boolean checkOutBook(int bookId, int memberSSN, Librarian librarian)
	    throws Exception {
	boolean heldByMember = false;
	boolean checkedOut = false;

	// can this member borrow the book?
	if (approveCheckout(bookId, memberSSN)) {
	    // check to see if the member is already holding the book...
	    heldByMember = checkMemberHold(bookId, memberSSN);

	    // set the date that the book is due
	    final int MILLISECONDS_IN_THREE_WEEKS = 1000 * 60 * 60 * 24 * 21;
	    java.util.Date d = new java.util.Date(System.currentTimeMillis()
		    + MILLISECONDS_IN_THREE_WEEKS);

	    // Format it nicely into a String.
	    SimpleDateFormat f = new SimpleDateFormat("MM/dd/yyyy");
	    String dd = f.format(d);

	    // if the book is not held by a member, check it out...
	    if (!heldByMember) {
		// Build the SQL statement required to check out the book.
		String sqlQuery = null;

		sqlQuery = new String("UPDATE Book SET borrowerssn = "
			+ memberSSN + ", librarianssn = " + librarian.getSSN()
			+ ", duedate = '" + dd + "' " + "WHERE bookid = "
			+ bookId);

		if (myConnection.runUpdate(sqlQuery) > 0)
		    return true;
	    } else {
		// otherwise, delete the hold and then check it out
		String callNumber = LibraryBook.getBook(bookId).getCallNumber();
		String[] sqlQuery = new String[2];
		sqlQuery[0] = "DELETE FROM hold WHERE ssn=" + memberSSN
			+ " and callnumber='" + callNumber + "'";
		sqlQuery[1] = "UPDATE Book SET borrowerssn = " + memberSSN
			+ ", librarianssn = " + librarian.getSSN()
			+ ", duedate = '" + dd + "' " + "WHERE bookid = "
			+ bookId;
		return myConnection.runChainedUpdate(sqlQuery,
			Connection.TRANSACTION_SERIALIZABLE);

	    }
	}
	return false;
    }

    /**
     * releaseHold releases a hold on booktitle with call number callNumber for
     * the specified member.
     * 
     * @param callNumber
     *            String call number of hold to release
     * @param member
     *            Member member who has the hold
     * @return boolean
     */
    public boolean releaseHold(String callNumber, Member member)
	    throws Exception {

	String sqlQuery = "DELETE FROM Hold WHERE ssn = " + member.getSSN()
		+ " AND CallNumber = '" + callNumber + "'";

	if (myConnection.runUpdate(sqlQuery) > 0)
	    return true;
	else
	    return false;
    }

    /**
     * validateLibrarian returns a librarian object for the librarian with the
     * given ssn and password
     * 
     * @param ssn
     *            String ssn of librarian
     * @param passWord
     *            String password of librarian
     * @return Librarian
     */
    public Librarian validateLibrarian(int ssn, String passWord)
	    throws Exception {

	String sql = "SELECT * FROM Librarian WHERE ssn = " + ssn
		+ " AND passwd = '" + passWord + "'";

	ResultSet r = myConnection.runQuery(sql);
	if (r == null) {
	    return null;
	}
	if (r.next()) {
	    return LibraryLibrarian.getLibrarian(r.getInt("ssn"));
	} else {
	    return null;
	}
    }

    /**
     * validateMember returns a new member for the given ssn and password
     * 
     * @param ssn
     *            String ssn of member
     * @param passWord
     *            String password of member
     * @return Member
     */
    public Member validateMember(int ssn, String passWord) throws Exception {

	String sql = "SELECT * FROM Member WHERE ssn = " + ssn
		+ " AND passwd = '" + passWord + "'";

	ResultSet r = myConnection.runQuery(sql);

	if (r == null) {
	    return null;
	}
	if (r.next()) {
	    return LibraryMember.getMember(r.getInt("ssn"));
	} else {
	    return null;
	}
    }

    /**
     * getBooks returns all of the books currently in the library
     * 
     * @return BookSet
     */
    public BookSet getBooks() throws Exception {

	String sqlQuery = "SELECT bookid FROM Book ORDER BY BookID ASC";
	BookSet currentBooks = new BookSet();

	ResultSet r = myConnection.runQuery(sqlQuery);
	while (r.next()) {
	    currentBooks.addBook(LibraryBook.getBook(r.getInt("bookid")));
	}
	r.close();

	return currentBooks;
    }

    /**
     * getBookTitles returns the set of all book titles current at the library
     * 
     * @return BookTitleSet
     */
    public BookTitleSet getBookTitles() throws Exception {

	String sqlQuery = "SELECT callnumber FROM Book ORDER BY BookID ASC";
	BookTitleSet currentBooks = null;

	ResultSet r = myConnection.runQuery(sqlQuery);
	while (r.next()) {
	    currentBooks.addBookTitle(LibraryBookTitle.getBookTitle(r
		    .getString("callnumber")));
	}
	return currentBooks;
    }

    public Library createMember(int userId, String dlState, String dlNum,
	    String fName, String lName, String street, String city,
	    String state, String postalCode, String phone, String email,
	    String password) throws Exception{
	
	String sql = "SELECT * FROM Member WHERE ssn = " + userId;
	ResultSet r = myConnection.runQuery(sql);
	if (r.next()) {
	    return null;
	}
	
	String insertSql = "INSERT INTO Member VALUES (" + userId + ",'"
				+ dlState + "','" + dlNum + "','" + fName + "','" + lName
				+ "','" + street + "','" + city + "','" + state + "','"
				+ postalCode + "','" + phone + "','" + email + "','" + password
				+ "')";
	myConnection.runUpdate(insertSql);
	return this;
    }
}
