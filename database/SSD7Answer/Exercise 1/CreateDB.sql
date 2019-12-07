Create Table Publisher
(PublisherID integer,
 Name char(50),
 Address char(30),
 Primary Key (PublisherID)
);

Create Table Book
("Primary Author" char(20),
 Title char(30),
 ISBN integer,
 PublisherID integer,
 Edition integer,
 "Date of Publication" char(20),
 Price numeric(4,2),
 "Book Description" char(50),
 Primary Key (ISBN),
 Foreign Key (PublisherID) References Publisher(PublisherID)
);

Insert Into Publisher
Values('2001','University of Illinois Press','Champaign,US');
Insert Into Publisher
Values('2002','Carnegie Mellon University Press','Pittsburgh,US');
Insert Into Publisher
Values('2003','University of Waterloo Press','Waterloo,Ca');
Insert Into Publisher
Values('2004','NWPU Press','NWPU Press');

Insert Into Book
Values('Han Jiawei','Date Mining','1001','2001','1','2005-01-01','30.00','Computer Science');
Insert Into Book
Values('Jackson','Bioinformatics','1002','2002','2','2006-01-01','40.00','Computer Science');
Insert Into Book
Values('Ross Butt','Pattern Recognition','1003','2003','3','2007-01-01','50.00','Computer Science');
Insert Into Book
Values('Zhang Yunpeng','SSD4','1004','2004','4','2008-01-01','60.00','Computer Science');

Select Book.Title,Book.Price 
From Book,Publisher
where Book.PublisherID = Publisher.PublisherID And
(Publisher.Name = 'University of Illinois Press' Or Publisher.Name = 'University of Waterloo Press');

Select Publisher.Name
From Publisher,Book
where Book.PublisherID = Publisher.PublisherID And Book.Title = 'Bioinformatics';