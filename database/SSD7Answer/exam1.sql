--1,
----1.1
SELECT A
FROM R;
----1.2
SELECT *
FROM R
WHERE B = 13;
----1.3
SELECT A, B
FROM R, S
WHERE A.C = S.D;

--2
----2.1
The result is:
Kasper   Spreadsheet   Admin 
Mohan    Spreadsheet   Admin 
Lin      Forecast      Admin 
Lin      Spreadsheet   Admin 
----2.2
no result. Because attributes of the relation r an relation s do not have the same number and domain.
----2.3
The result is empty table.

--4
----4.1
ALTER TABLE orders 
ALTER COLUMN received SET NOT NULL;
----4.2
ALTER TABLE orders 
ADD CHECK(Shipped > Received OR Shipped IS NULL);

--5
----5.1
SELECT pno 
FROM part
WHERE unitprice BETWEEN 10.00 AND 25.00;
----5.2
SELECT SUM(qty), part.pno
FROM invoice NATURAL JOIN orders NATURAL JOIN part
WHERE part.pno=invoice.pno AND invoice.ono=orders.ono AND orders.shipped LIKE '%98'
GROUP BY part.pno
ORDER BY SUM(billedprice) ASC;
----5.3
SELECT *
FROM part
WHERE pno NOT IN
	(SELECT pno 
	FROM orders,invoice
	WHERE orders.ono=invoice.ono AND received NOT LIKE '%98');

--6
ALTER TABLE employee
ADD FOREIGN KEY (dname) REFERENCES department(name);S