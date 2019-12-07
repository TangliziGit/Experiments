import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import library.Library;
import library.LibraryMember;
import library.Member;

/**
 * Servlet implementation class MemberRegisterController
 */
public class MemberRegisterController extends Controller
{
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public MemberRegisterController()
	{
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException
	{

		String dlState = null;
		String dlNum = null;
		String fName = null;
		String lName = null;
		String street = null;
		String city = null;
		String state = null;
		String postalCode = null;
		String phone = null;
		String email = null;
		String password = null;

		int uname = -1;

		// Get the HttpSession object.
		HttpSession session = request.getSession();
		// Invalidate session to get rid of any old Member or Librarian objects.
		session.invalidate();

		// Get a fresh session.
		session = request.getSession();

		// Create a Library object instance.
		Library library = null;

		// Create a new instance of the Library object.
		try
		{
			library = new Library();
		}
		catch (Exception e)
		{
			sendErrorRedirect(request, response, e);
			return;
		}

		// Get the parameters.
		try
		{
			// Get the uname parameter.
			uname = (request.getParameter("uname") == null) ? 0 : Integer
					.parseInt(request.getParameter("uname"));
		}
		catch (NumberFormatException nfe)
		{
			response.sendRedirect(request.getContextPath()
					+ "/newmember.jsp?uname=" + request.getParameter("uname")
					+ "&errMsg=UserID has to be an integer!");
			return;
		}
		password = request.getParameter("password");
		dlState = request.getParameter("dlstate");
		dlNum = request.getParameter("dlnum");
		fName = request.getParameter("fname");
		lName = request.getParameter("lname");
		street = request.getParameter("street");
		city = request.getParameter("city");
		state = request.getParameter("state");
		postalCode = request.getParameter("pcode");
		phone = request.getParameter("phone");
		email = request.getParameter("email");
		
		// creating Member
		try
		{
			library = library.createMember(uname, dlState, dlNum, fName, lName,
					street, city, state, postalCode, phone, email, password);
			if (library == null)
			{
				response.sendRedirect(request.getContextPath()
						+ "/newmember.jsp?uname="
						+ request.getParameter("uname")
						+ "&errMsg=UserID not available: Already in use");
				return;
			}
			else
			{
				Member member = LibraryMember.getMember(uname);
				if (member != null)
				{
					session.setAttribute("member", member);
					response.sendRedirect(request.getContextPath() + "/memberaccount.jsp");
					return;
				}
				else
				{
					/**
					 * Just added to check if member comes null coz of some problem
					 */
					response.sendRedirect(request.getContextPath()
							+ "/member.jsp?uname=" + request.getParameter("uname")
							+ "&errMsg=Incorrect User id and/or password");
					return;
				}
			}
		}
		catch (Exception e)
		{
			sendErrorRedirect(request, response, e);
			return;
		}

		// Create a new library member through validation. If the uname is not
		// valid, the member is null.

	}

}
