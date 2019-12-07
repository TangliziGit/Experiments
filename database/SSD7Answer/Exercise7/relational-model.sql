--1.create table "Category"
CREATE TABLE Category(
Category_id	char(20) NOT NULL,
CategoryName	char(30),
SubCategory_id	char(20),
PRIMARY KEY (Category_id),
FOREIGN KEY (SubCategory_id) REFERENCES Category(Category_id)
);

--2.create table "Publisher"
CREATE TABLE Publisher(
Publisher_id	char(20) NOT NULL,
PublisherName	char(30),
PublisherAddress	char(40),
PRIMARY KEY (Publisher_id)
);

--3.create table "BookTitle"          
CREATE TABLE BookTitle(
ISBN	char(20) NOT NULL, 
Author	char(30),
Title	char(30), 
Publisher_id	char(20), 
Edition	char(30), 
PublicationDate	date, 
Price	float, 
BookDescription	char(100), 
Category_id	char(20), 
Order_num	char(20),
PRIMARY KEY (ISBN),
FOREIGN KEY (Publisher_id) REFERENCES Publisher(Publisher_id),
FOREIGN KEY (Category_id) REFERENCES Category(Category_id), 
FOREIGN KEY (Order_num) REFERENCES Orders(Order_num)
);

--4.create table "Promotion"
CREATE TABLE Promotion(
Promotion_id	char(20) NOT NULL, 
Discount	float, 
StartDate	date, 
EndDate         date,
PRIMARY KEY (Promotion_id)
);

--5.create table "Shipment"
CREATE TABLE Shipment(
Tracking_num	char(20) NOT NULL, 
ShipmentDate	date, 
ExpectedDate	date,
PRIMARY KEY (Tracking_num)
);

--6.create table "Orders"              
CREATE TABLE Orders(
Order_num        char(20) NOT NULL,
Customer_id      char(20),
Tracking_num	 char(20),
MailAddress      char(100),
MethodShipment   char(20),
ShippingDate     date,
DateOrderTime    integer,
PRIMARY KEY (Order_num),
FOREIGN KEY (Customer_id) REFERENCES Customer(Customer_id),
FOREIGN KEY (Tracking_num) REFERENCES Shipment(Tracking_num)
);

--7.create table "Customer"
CREATE TABLE Customer(
Customer_id	char(20) NOT NULL, 
CustomerName	char(30), 
MailAddress	char(100), 
CreditNumer	char(20), 
EmailAddress	char(100),
PRIMARY KEY (Customer_id)
);

--8.create table "LineItem"
CREATE TABLE LineItem(
ISBN              char(20),
Tracking_num      integer,
Order_num         char(20),
ShippingCost      float,
PurchasedQuantity char(20),
BookPrice         float,
Tax               float,
PRIMARY KEY (ISBN, Tracking_num),
FOREIGN KEY (ISBN) REFERENCES BookTitle(ISBN),
FOREIGN KEY (Order_num) REFERENCES Orders(Order_num),
FOREIGN KEY (Tracking_num) REFERENCES Shipment(Tracking_num)
);

--9.create table "Book_Promotion"
CREATE TABLE Book_Promotion(
ISBN	char(20),
Promotion_id	char(20),
PRIMARY KEY (ISBN, Promotion_id),
FOREIGN KEY (ISBN) REFERENCES BookTitle(ISBN),
FOREIGN KEY (Promotion_id) REFERENCES Promotion(Promotion_id)
);
