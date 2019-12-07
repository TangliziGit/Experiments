CREATE TABLE PUBLISHER
(
	PublisherID   int not null,
	Name          char(40) not null,
	Address       char(100) not null,
	primary key (PublisherID),
	unique (Name,Address)
);



CREATE TABLE BOOK
(
	Title         char(80) not null,
	ISBN          char(21) not null,
	Edition       int,
	PublishDate  date not null,
	Description   char(80),
	PublisherID  int ,
	CategoryID   int,
	primary key (ISBN),
	foreign key (PublisherID) references PUBLISHER(PublisherID),
	foreign key (CategoryID) references CATEGORY(CategoryID)
);

CREATE TABLE AUTHOR
(
	AuthorName char(40) not null,
	AuthorID    int not null,
	primary key (AuthorID)
);


CREATE TABLE CATEGORY
(
	CategoryID    int not null,
	CategoryName  char(40) not null,
	SuperID       int,
	primary key (CategoryID),
	unique (CategoryName),
	foreign key (SuperID) references CATEGORY(CategoryID)
);


CREATE TABLE CUSTOMER
(
	CustomerID    char(10) not null,
	CustomerName  char(40) not null,
	MailAddress   char(100) not null,
	CreditNumer   int not null,
	EmailAddress  char(40) not null,
	primary key (CustomerID)
);

CREATE TABLE PROMOTION
(
	PromotionNumber       int not null,
	Discount              float not null,
	StartDate             date not null,
	EndDate               date not null,
	primary key (PromotionNumber)
);

CREATE TABLE ORDERS
(
	OrderNumber   int not null,
	MailAddress   char(100) not null,
	Method        char(10) not null,
	DateTime      date not null,
	TotalPrice    float not null,
	CustomerID    char(10) not null,
	primary key (OrderNumber),
	foreign key (CustomerID) references CUSTOMER(CustomerID)
);

CREATE TABLE SHIPMENT
(
	TrackingNumber int8 not null,
	ShipmentDate   date not null,
	ExpectedDate   date not null,
	OrderNumber    int not null,
	primary key (TrackingNumber),
	foreign key (OrderNumber) references ORDERS(OrderNumber)
);


CREATE TABLE PROMOTE
(
	PromotionNumber   int not null,
	ISBN              char(21) not null,
	primary key (PromotionNumber,ISBN),
	foreign key (PromotionNumber) references PROMOTION(PromotionNumber),
	foreign key (ISBN) references BOOK(ISBN)
);

CREATE TABLE ORDERITEM
(
	OrderNumber  int not null,
	Book         char(21) not null,
	Quantity     int not null,
	Price        float not null,
	primary key (OrderNumber,Book),
	foreign key (OrderNumber) references ORDERS(OrderNumber),
	foreign key (Book) references BOOK(ISBN)
);

CREATE TABLE WRITES
(
	ISBN        char(21) not null,
	AuthorID    int not null,
	primary key (ISBN,AuthorID),
	foreign key (ISBN) references BOOK(ISBN),
	foreign key (AuthorID) references AUTHOR(AuthorID)
);

