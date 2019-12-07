




SELECT name, year FROM title WHERE callnumber = (SELECT callnumber FROM author WHERE lname = 'Churchill');






SELECT name FROM title WHERE callnumber IN (SELECT callnumber FROM book WHERE borrowermemno IN (SELECT memno
		FROM member
		WHERE fname = 'John' OR fname = 'Susan'));








(SELECT memno, fname, lname FROM member WHERE memno IN (SELECT borrowermemno FROM book WHERE callnumber IN (SELECT callnumber FROM title WHERE name = 'Iliad')))
INTERSECT
(SELECT memno, fname, lname FROM member WHERE memno IN (SELECT borrowermemno  FROM book WHERE callnumber IN (SELECT callnumber FROM title WHERE name = 'Odyssey')));







SELECT memno, fname, lname FROM member WHERE NOT EXISTS (SELECT * FROM author WHERE author.lname = 'Collins' AND NOT EXISTS(SELECT * FROM book WHERE member.memno = book.borrowermemno AND author.callnumber = book.callnumber));







SELECT phonenumber FROM member WHERE memno IN(SELECT borrowermemno FROM book WHERE callnumber IN (SELECT callnumber
		FROM author
		WHERE lname = 'Tanenbaum'));






SELECT memno, fname, lname, COUNT(*) FROM member, book WHERE memno = borrowermemno GROUP BY memno, fname, lname HAVING COUNT(*) > 3 ORDER BY COUNT(*) DESC;







SELECT * FROM member WHERE NOT EXISTS(SELECT * FROM title WHERE EXISTS(SELECT *FROM book
WHERE member.memno = book.borrowermemno AND title.callnumber = book.callnumber));






SELECT * FROM member WHERE phonenumber LIKE '412%' AND NOT EXISTS (SELECT * FROM title WHERE name = 'Pitt Roads' AND EXISTS(SELECT * FROM book
WHERE member.memno = book.borrowermemno AND title.callnumber = book.callnumber)) ORDER BY Fname ASC;
		