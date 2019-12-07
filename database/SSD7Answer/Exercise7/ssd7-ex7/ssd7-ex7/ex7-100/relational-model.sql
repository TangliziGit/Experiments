CREATE TABLE Book(
Title VARCHAR(200),
ISBN VARCHAR(40) NOT NULL,
Publisher_id VARCHAR(40) NOT NULL,
Author VARCHAR(40),
Edition INTEGER,
PublicationDate DATE,
Price FLOAT,
Book Description VARCHAR(600),
PRIMARY KEY (ISBN),
FOREIGN KEY (Publisher_id) REFERENCES Publisher(Publisher_id)
);

CREATE TABLE Author(
Author_id VARCHAR(40) NOT NULL, 
Name VARCHAR(120),
PRIMARY KEY (Author_id),
ALTERABLE KEY (Name)
);

CREATE TABLE Publisher(
Publisher_id VARCHAR(40) NOT NULL,
Publisher Name VARCHAR(200),
Address VARCHAR(300),
PRIMARY KEY (Publisher_id)
);

CREATE TABLE Customer(
Customer_id VARCHAR(40) NOT NULL,
Name VARCHAR(60),
CreditCardNumber VARCHAR(40),
Mailing Address VARCHAR(100),
PhoneNumber VARCHAR(40),
EmailAddress VARCHAR(40),
PRIMARY KEY (Customer_id),
);

CREATE TABLE Shipment(
Tracking Number INTEGER NOT NULL,
Date DATE,
Method VARCHAR(60),
PRIMARY KEY (Tracking Number),
);

CREATE TABLE Order(
Order_num VARCHAR(40) NOT NULL,
Customer_id VARCHAR(40),
MethodShipment VARCHAR(40),
ShippingDate DATE,
OrderTime TIMESTAMP,
PRIMARY KEY (OrderNumber),
FOREIGN KEY (Customer_id) REFERENCES Customer(Customer_id),
);

CREATE TABLE Promotion(
Promotion_id VARCHAR(40) NOT NULL,
DiscountPercentage FLOAT,
StartDate DATE,
EndDate DATE,
PRIMARY KEY (Promotion_id),
);

CREATE TABLE Category(
Category_id VARCHAR(40) NOT NULL,
Category_Name VARCHAR(40),
Supercategory_id VARCHAR(40),
PRIMARY KEY (Category_id),
FOREIGN KEY (Supercategory_id) REFERENCES Category(Category_id),
);

CREATE TABLE LineItem(
ISBN VARCHAR(40) NOT NULL,
Tracking Number INTEGER NOT NULL,
Order_Number VARCHAR(40), 
Shipping Price FLOAT,
Purchased Quantity VARCHAR(60),
Book Price FLOAT,
PRIMARY KEY (ISBN, Tracking_Number),
FOREIGN KEY (ISBN) REFERENCES Book(ISBN),
FOREIGN KEY (Order_Number) REFERENCES Order(Order_num),
FOREIGN KEY (Tracking_Number) REFERENCES Shipment(Tracking_Number),
);

CREATE TABLE Book_Promotion(
ISBN VARCHAR(40) NOT NULL,
Promotion_id VARCHAR(40) NOT NULL,
PRIMARY KEY (ISBN, Promotion_id),
FOREIGN KEY (ISBN) REFERENCES Book(ISBN)
FOREIGN KEY (Promotion_id) REFERENCES Promotion(Promotion_id),
);

CREATE TABLE Book_Category(
ISBN VARCHAR(40) NOT NULL,
Category_id VARCHAR(40) NOT NULL,
PRIMARY KEY(ISBN, Category_id)
FOREIGN KEY (ISBN) REFERENCES Book(SIBN)
FOREIGN KEY (Category_id) REFERENCES Category(Category_id)
);

CREATE TABLE Book_Author(
ISBN VARCHAR(40) NOT NULL,  
Author_id VARCHAR(40) NOT NULL,
PRIMARY KEY(ISBN, Author_id)
FOREIGN KEY(ISBN) REFERENCES Book(ISBN)
FOREIGN KEY(Author_id) REFERENCES Author(Author_id)
);






