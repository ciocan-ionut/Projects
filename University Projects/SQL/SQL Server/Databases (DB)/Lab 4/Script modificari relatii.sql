CREATE TABLE LegaturiEliminate(
	NumeTabelSt nvarchar(30),
	IdSt int,
	NumeTabelDr nvarchar(30),
	IdDr int
)
SELECT * FROM LegaturiEliminate

-- 1:N -> N:1
SELECT * FROM Teams
SELECT * FROM TeamPrincipals

ALTER TABLE TeamPrincipals
ADD TeamID INT FOREIGN KEY REFERENCES Teams(ID)

UPDATE TP
SET TP.TeamID = (
	SELECT MAX(T.ID)
	FROM Teams T
	WHERE T.TPID = TP.ID
)
FROM TeamPrincipals TP

INSERT INTO LegaturiEliminate(NumeTabelSt, IdSt, NumeTabelDr, IdDr)
SELECT 'TeamPrincipals', TP.ID, 'Teams', T.ID
FROM TeamPrincipals TP
JOIN Teams T ON TP.ID = T.TPID
WHERE T.ID NOT IN (
	SELECT MAX(T2.ID)
	FROM Teams T2
	WHERE T2.TPID = TP.ID
)

DELETE FROM Teams
WHERE EXISTS (
	SELECT * FROM LegaturiEliminate
	WHERE ID = IdDr AND NumeTabelDr LIKE 'Teams'
)

ALTER TABLE Teams
DROP CONSTRAINT FK__TEAMS__TPID__628FA481

ALTER TABLE Teams
DROP COLUMN TPID

-- 1:N -> M:N
SELECT * FROM Engineers
SELECT * FROM DepartmentHeads
SELECT * FROM DepartmentHeads_Engineers

CREATE TABLE DepartmentHeads_Engineers(
	DHID int foreign key references DepartmentHeads(ID),
	EngID int foreign key references Engineers(ID),
	primary key (DHID, EngID)
)

INSERT INTO DepartmentHeads_Engineers
SELECT DHID, ID
FROM Engineers

ALTER TABLE Engineers
DROP CONSTRAINT FK__Engineers__DHID__29221CFB

ALTER TABLE Engineers
DROP COLUMN DHID

-- 1:N -> 1:1
SELECT * FROM Drivers
SELECT * FROM Cars

ALTER TABLE Cars
ADD DriverID int

UPDATE C
SET C.DriverID = (
	SELECT MAX(D.ID)
	FROM Drivers D
	WHERE C.ID = D.CarID
)
FROM Cars C;

ALTER TABLE Cars
ADD CONSTRAINT UQ__Cars__DriverID UNIQUE(DriverID)

ALTER TABLE Cars
ADD CONSTRAINT FK__Cars__DriverID FOREIGN KEY(DriverID) REFERENCES Drivers(ID) 

INSERT INTO LegaturiEliminate
SELECT 'Cars', C.ID, 'Drivers', D.ID
FROM Cars C
JOIN Drivers D ON C.ID = D.CarID
WHERE D.ID NOT IN (
	SELECT MAX(D2.ID)
	FROM Drivers D2
	WHERE C.ID = D2.CarID
)

DELETE FROM Drivers
WHERE EXISTS (
	SELECT * FROM LegaturiEliminate
	WHERE ID = IdDr AND NumeTabelDr LIKE 'Drivers'
)

ALTER TABLE Drivers
DROP CONSTRAINT FK__Drivers__CarID__693CA210

ALTER TABLE Drivers
DROP COLUMN CarID

-- M:N -> 1:N
SELECT * FROM Calendars
SELECT * FROM Tracks
SELECT * FROM Races

ALTER TABLE Tracks
ADD CalendarID int foreign key references Calendars(ID)

UPDATE T
SET T.CalendarID = (
	SELECT MAX(R.CalendarID)
	FROM Races R
	WHERE T.ID = R.TrackID
)
FROM Tracks T

INSERT INTO LegaturiEliminate
SELECT 'Calendars', R.CalendarID, 'Tracks', R.TrackID
FROM Races R
WHERE R.CalendarID NOT IN (
	SELECT MAX(R2.CalendarID)
	FROM Races R2
	WHERE R.TrackID = R2.TrackID
)

ALTER TABLE Races
DROP CONSTRAINT FK__Races__CalendarI__73BA3083

ALTER TABLE Races
DROP CONSTRAINT FK__Races__TrackID__74AE54BC

DROP TABLE Races