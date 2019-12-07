--5, SQL queries 
----5.1, Display the ID, first name, and joining date of each member whose ID begins with the letters "A%B" or "A&B" 
----and who joined the library no later than Nov. 30, 1997. 
SELECT libid, fname, join_date
FROM member4
WHERE (libid LIKE 'A/%B%' ESCAPE '/' OR libid LIKE 'A&B%') AND (join_date <= '1997/11/30');

----5.2, List the name, ISBN, and call number of each title, provided it has been ordered from more than one supplier 
----and the total quantity ordered is more than 10. The list should be arranged in non-increasing order of the total quantity ordered. 
SELECT name, isbn, callnumber, SUM(qty)
FROM title4 NATURAL JOIN ordered4 NATURAL JOIN purchase_order4
WHERE title4.callnumber IN (SELECT callnumber
	FROM purchase_order4 NATURAL JOIN ordered4
	GROUP BY callnumber
	HAVING SUM(qty) > 10)
GROUP BY name, isbn, callnumber
HAVING COUNT(supplier_id) > 1
ORDER BY SUM(qty) DESC;

----5.3, List the IDs and first names of all the members who have read less than 5% of the total number of books read 
----from the library, in non-decreasing order of the number of books read by each. 
SELECT libid, fname, SUM(timesread)
FROM member4 NATURAL JOIN read_by4
GROUP BY member4.libid, member4.fname
HAVING SUM(timesread) < (SELECT 0.05*SUM(timesread)
			FROM read_by4)
ORDER BY SUM(timesread);

----5.4, List in alphabetical order the first names and IDs of all female members of the library who have read 
----at least one title more than once. 
SELECT DISTINCT member4.fname, member4.libid
FROM member4 NATURAL JOIN read_by4
GROUP BY member4.fname, member4.libid, member4.gender, read_by4.timesread
HAVING member4.gender = 'F' AND read_by4.timesread > 1
ORDER BY member4.fname;

----5.5, List the names of the suppliers and their respective average quantities of title orders received, 
----whose average quantities of title orders received is more than the average quantity of an order in the system. 
SELECT name, AVG(qty)
FROM supplier4 NATURAL JOIN ordered4 NATURAL JOIN purchase_order4
GROUP BY supplier4.name, supplier4.supplier_id
HAVING AVG(qty) > (SELECT AVG(qty)
		FROM purchase_order4);

----5.6, List alphabetically the first names and IDs of all the male members of the library who joined before 
----Oct. 10, 1995, who have read only five or fewer different titles, and who have not read the same title twice or more. 
SELECT fname, libid
FROM member4 NATURAL JOIN read_by4
GROUP BY fname, libid, join_date, gender
HAVING join_date < '1995/10/10' AND gender = 'M'

INTERSECT

SELECT fname, libid
FROM member4 NATURAL JOIN read_by4
GROUP BY fname, libid, join_date
HAVING COUNT(callnumber) <= 5

INTERSECT

SELECT fname, libid
FROM member4 NATURAL JOIN read_by4
GROUP BY fname, libid, join_date, timesread
HAVING timesread < 2;

