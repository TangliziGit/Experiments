/*
*@author:wangzhesi
*053597
*/
CREATE TABLE Book(
Author          char(40),
Title           char(40),
ISBN            char(20) not null,
Publisher_id    char(40) not null,
Edition         char(40),
PublicationDate date,
Price           float,
BookDescription char(100),
Categories_id   char(40) not null,
PRIMARY KEY (ISBN),
FOREIGN KEY (Publisher_id) REFERENCES Publisher(Publisher_id),
FOREIGN KEY (PCategories_id) REFERENCES Categories(Categories_id)
);

CREATE TABLE Publisher(
Publisher_id     char(40) not null,
PublisherName    char(40),
PublisherAddress char(40),
PRIMARY KEY (Publisher_id)
);

CREATE TABLE Author(
Author_id       char(40) not null,
AuthorName      char(40),
PRIMARY KEY (Author_id)
);

CREATE TABLE Categories(
Categories_id    char(40),
CategoriesName   char(40),
SubCategories_id char(40),
PRIMARY KEY (Categories_id),
FOREIGN KEY (SubCategories_id) REFERENCES Categories(Categories_id)
);

CREATE TABLE Promotion(
Promotion_id     char(40) not null,
Discount         float,
StartDate        date,
EndDate          date,
PRIMARY KEY (Promotion_id)
);

CREATE TABLE Orders(
Order_num        char(40) NOT NULL,
Customer_id      char(40),
MailAddress      char(100)
MethodShipment   char(40),
ShippingDate     date,
DateOrderTime    integer,
PRIMARY KEY (Order_num),
FOREIGN KEY (Customer_id) REFERENCES Customer(Customer_id)
);

CREATE TABLE Customer(
Customer_id    char(40),
CustomerName   char(40), 
MailAddress    char(100),
CreditNumer    integer,
EmailAddress   char(40),
PRIMARY KEY (Customer_id)
);

CREATE TABLE Shipment(
Tracking_num  integer,
ShipmentDate  date,
Order_num     char(40),
ExpectedDate  date,
PRIMARY KEY (Tracking_num)
);

CREATE TABLE LineItem(
ISBN              char(40),
Tracking_num      integer,
Order_num         char(40),
ShippingCost      float,
PurchasedQuantity char(40),
BookPrice         float,
Tax               float,
PRIMARY KEY (ISBN, Tracking_num),
FOREIGN KEY (ISBN) REFERENCES Book(ISBN),
FOREIGN KEY (Order_num) REFERENCES Orders(Order_num),
FOREIGN KEY (Tracking_num) REFERENCES Shipment(Tracking_num)
);

CREATE TABLE Book_Promotion(
ISBN                           char(40),
Promotion_id              char(40),
PRIMARY KEY (ISBN, Promotion_id),
FOREIGN KEY (ISBN) REFERENCES Book(ISBN)
FOREIGN KEY (Promotion_id) REFERENCES Promotion(Promotion_id),
);

CREATE TABLE Book_Author(
ISBN                           char(40),  
Author_id                    char(40),
PRIMARY KEY(ISBN, Author_id)
FOREIGN KEY(ISBN) REFERENCES Book(ISBN)
FOREIGN KEY(Author_id) REFERENCES Author(Author_id)
);

CREATE TABLE Book_Category(
ISBN                            char(40),
Category_id                 char(40),
PRIMARY KEY(ISBN, Category_id)
FOREIGN KEY (ISBN) REFERENCES Book(SIBN)
FOREIGN KEY (Category_id) REFERENCES Category(Category_id)
);

