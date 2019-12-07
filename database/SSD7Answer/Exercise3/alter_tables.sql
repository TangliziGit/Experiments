--1, create tables which have not been created.
----1.1, create table purchase_order4
CREATE TABLE purchase_order4
(
  ponum char(8) NOT NULL,
  qty char(4),
  orderdate date,
  duedate date,
  receiveddate date,
  PRIMARY KEY (ponum)
);

----1.2, create table supplier4
CREATE TABLE supplier4
(
  supplier_id char(8) NOT NULL,
  name char(8),
  address char(15),
  PRIMARY KEY (supplier_id)
);

----1.3, create table read_by4
CREATE TABLE read_by4
(
  callnumber char(8) NOT NULL,
  libid char(6) NOT NULL,
  timesread char(4),
  PRIMARY KEY (callnumber, libid),
--  FOREIGN KEY (callnumber) REFERENCES title4(callnumber),
--  FOREIGN KEY (libid) REFERENCES member4(libid)
);

----1.4, create table ordered4
CREATE TABLE ordered4
(
  callnumber char(8) NOT NULL,
  ponum char(8) NOT NULL,
  supplier_id char(8) NOT NULL,
  PRIMARY KEY (callnumber, ponum, supplier_id),
--  FOREIGN KEY (callnumber) REFERENCES title4(callnumber),
--  FOREIGN KEY (ponum) REFERENCES purchase_order4(ponum),
--  FOREIGN KEY (supplier_id) REFERENCES supplier4(supplier_id)
);

--2, Add the constraint that ISBN and Name fields are alternate keys in the TITLE4 table and that they cannot take a NULL value. 
ALTER TABLE title4
ADD UNIQUE(isbn, name),
ALTER COLUMN isbn SET NOT NULL,
ALTER COLUMN name SET NOT NULL;

--3, Add referential integrity constraints as specified in all the tables. 
ALTER TABLE read_by4
ADD FOREIGN KEY (callnumber) REFERENCES title4(callnumber),
ADD FOREIGN KEY (libid) REFERENCES member4(libid);

ALTER TABLE ordered4
ADD FOREIGN KEY (callnumber) REFERENCES title4(callnumber),
ADD FOREIGN KEY (ponum) REFERENCES purchase_order4(ponum),
ADD FOREIGN KEY (supplier_id) REFERENCES supplier4(supplier_id);

--4, Add the columns "Join_date" and "Gender" to the MEMBER4 relation. 
ALTER TABLE member4
ADD join_date date
ADD gender char(4);

--5, Specify that the column "TimesRead" in READ_BY4 relation cannot have negative values. 
ALTER TABLE read_by4
ADD CHECK(timesread >= 0);
