create database Formula1

create table Calendars(
	ID int primary key identity(1, 1),
	Year int,
)

create table Tracks(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Location nvarchar(100),
	Length float,
	NrOfCorners int,
	AvgSpeed float
)

create table TeamPrincipals(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Salary float,
	ContractExpDate date
)

create table Teams(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Budget float,
	Location nvarchar(100),
	TPID int foreign key references TeamPrincipals(ID)
)

create table Cars(
	ID int primary key identity(1, 1),
	Number int,
	Engine nvarchar(30),
	HP int,
	TeamID int foreign key references Teams(ID)
)

create table Drivers(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Salary float,
	ContractExpDate date,
	TeamID int foreign key references Teams(ID),
	CarID int foreign key references Cars(ID)
)

create table Engineers(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Salary float,
	ContractExpDate date,
	Department nvarchar(100),
	TeamID int foreign key references Teams(ID)
)

create table PitStops(
	CarID int foreign key references Cars(ID),
	EngineerID int foreign key references Engineers(ID),
	Duration time(7),
	primary key(CarID, EngineerID)
)

create table Races(
	ID int primary key identity(1, 1),
	CalendarID int foreign key references Calendars(ID),
	TrackID int foreign key references Tracks(ID),
	StartDate date,
	EndDate date,
	unique (CalendarID, TrackID)
)

create table Podiums(
	DriverID int foreign key references Drivers(ID),
	RaceID int foreign key references Races(ID),
	Place int,
	primary key(DriverID, RaceID)
)

create table DepartmentHeads(
	ID int primary key identity(1, 1),
	Name nvarchar(100),
	Salary float,
	ContractExpDate date,
)

alter table Engineers
add DHID int foreign key references DepartmentHeads(ID);

BACKUP DATABASE Formula1
TO DISK = 'C:\Backup\Formula1.bak'
WITH FORMAT, INIT;

RESTORE DATABASE Formula1
FROM DISK = 'C:\Backup\Formula1.bak'
WITH REPLACE;