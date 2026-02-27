-- Constraints
ALTER TABLE Calendars
ADD CONSTRAINT CK_Year CHECK (Year >= 1950)

ALTER TABLE Tracks
ADD CONSTRAINT UQ_Name UNIQUE (Name)

ALTER TABLE Tracks
ADD CONSTRAINT CK_Length CHECK (Length > 0)

ALTER TABLE Tracks
ADD CONSTRAINT CK_Corners CHECK (NrOfCorners > 0)

ALTER TABLE Tracks
ADD CONSTRAINT CK_Speed CHECK (AvgSpeed > 0)

ALTER TABLE Races
ADD CONSTRAINT CK_StartDate CHECK (YEAR(StartDate) >= 1950)

ALTER TABLE Races
ADD CONSTRAINT CK_EndDate CHECK (DATEDIFF(DAY, StartDate, EndDate) = 2)

-- Calendar
CREATE OR ALTER PROCEDURE AddCalendar
	@Year INT,
	@ID INT OUTPUT
AS
BEGIN
	IF @Year >= 2027
	BEGIN
		RAISERROR('Invalid year!', 16, 1)
		RETURN
	END

	INSERT INTO Calendars(Year)
	VALUES (@Year)

	SET @ID = SCOPE_IDENTITY()
END

CREATE OR ALTER PROCEDURE FindCalendarByID
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	SELECT * FROM Calendars
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE UpdateCalendar
	@ID INT,
	@Year INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	IF @Year >= 2027
	BEGIN
		RAISERROR('Invalid year!', 16, 1)
		RETURN
	END

	UPDATE Calendars
	SET Year = @Year
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE DeleteCalendar
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	DELETE FROM Calendars
	WHERE ID = @ID
END

-- Functions
CREATE OR ALTER FUNCTION ValidateString(@String VARCHAR(100))
RETURNS BIT
AS
BEGIN
	IF LEN(@String) < 4
		RETURN 0
	RETURN 1
END

-- Tracks
CREATE OR ALTER PROCEDURE AddTrack
	@Name VARCHAR(100),
	@Location VARCHAR(100),
	@Length FLOAT,
	@Corners INT,
	@AvgSpeed FLOAT,
	@ID INT OUTPUT
AS
BEGIN
	IF dbo.ValidateString(@Name) = 0
	BEGIN
		RAISERROR('Name is too short!', 16, 1)
		RETURN
	END

	IF dbo.ValidateString(@Location) = 0
	BEGIN
		RAISERROR('Location is too short!', 16, 1)
		RETURN
	END
	
	INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
	VALUES (@Name, @Location, @Length, @Corners, @AvgSpeed)

	SET @ID = SCOPE_IDENTITY()
END

CREATE OR ALTER PROCEDURE FindTrackByID
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	SELECT * FROM Tracks
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE UpdateTrack
	@ID INT,
	@Name VARCHAR(100),
	@Location VARCHAR(100),
	@Length FLOAT,
	@Corners INT,
	@AvgSpeed FLOAT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	IF dbo.ValidateString(@Name) = 0
	BEGIN
		RAISERROR('Name is too short!', 16, 1)
		RETURN
	END

	IF dbo.ValidateString(@Location) = 0
	BEGIN
		RAISERROR('Location is too short!', 16, 1)
		RETURN
	END

	UPDATE Tracks
	SET Name = @Name, Location = @Location, Length = @Length,
		NrOfCorners = @Corners, AvgSpeed = @AvgSpeed
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE DeleteTrack
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	DELETE FROM Tracks
	WHERE ID = @ID
END

-- Races
CREATE OR ALTER PROCEDURE AddRace
	@CalendarID INT,
	@TrackID INT,
	@StartDate DATE,
	@EndDate DATE,
	@ID INT OUTPUT
AS
BEGIN
	IF @CalendarID <= 0
	BEGIN
		RAISERROR('Invalid Calendar ID!', 16, 1)
		RETURN
	END

	IF @TrackID <= 0
	BEGIN
		RAISERROR('Invalid Track ID!', 16, 1)
		RETURN
	END

	INSERT INTO Races(CalendarID, TrackID, StartDate, EndDate)
	VALUES (@CalendarID, @TrackID, @StartDate, @EndDate)

	SET @ID = SCOPE_IDENTITY()
END

CREATE OR ALTER PROCEDURE FindRaceByID
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	SELECT * FROM Races
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE UpdateRace
	@ID INT,
	@CalendarID INT,
	@TrackID INT,
	@StartDate DATE,
	@EndDate DATE
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	IF @CalendarID <= 0
	BEGIN
		RAISERROR('Invalid Calendar ID!', 16, 1)
		RETURN
	END

	IF @TrackID <= 0
	BEGIN
		RAISERROR('Invalid Track ID!', 16, 1)
		RETURN
	END

	UPDATE Races
	SET CalendarID = @CalendarID, TrackID = @TrackID,
		StartDate = @StartDate, EndDate = @EndDate
	WHERE ID = @ID
END

CREATE OR ALTER PROCEDURE DeleteRace
	@ID INT
AS
BEGIN
	IF @ID <= 0
	BEGIN
		RAISERROR('Invalid ID!', 16, 1)
		RETURN
	END

	DELETE FROM Races
	WHERE ID = @ID
END

-- Logs
CREATE TABLE LogCalendars(
	ID INT PRIMARY KEY IDENTITY,
	CalendarID INT,
	Year INT,
	Operation VARCHAR(20),
	OpDate DATETIME DEFAULT GETDATE(),
	loginSQL VARCHAR(100)
)

CREATE TABLE LogTracks(
	ID INT PRIMARY KEY IDENTITY,
	TrackID INT,
	Name VARCHAR(100),
	Location VARCHAR(100),
	Length FLOAT,
	NrOfCorners INT,
	AvgSpeed FLOAT,
	Operation VARCHAR(20),
	OpDate DATETIME DEFAULT GETDATE(),
	loginSQL VARCHAR(100)
)

CREATE TABLE LogRaces(
	ID INT PRIMARY KEY IDENTITY,
	RaceID INT,
	CalendarID INT,
	TrackID INT,
	StartDate DATE,
	EndDate DATE,
	Operation VARCHAR(20),
	OpDate DATETIME DEFAULT GETDATE(),
	loginSQL VARCHAR(100)
)

-- Triggers
CREATE TRIGGER TR_Update_Calendars
ON Calendars
FOR UPDATE
AS
BEGIN
	INSERT INTO LogCalendars(CalendarID, Year, Operation, loginSQL)
	SELECT d.ID, d.Year, 'UPDATE', SYSTEM_USER
	FROM deleted d
END

CREATE TRIGGER TR_Delete_Calendars
ON Calendars
FOR DELETE
AS
BEGIN
	INSERT INTO LogCalendars(CalendarID, Year, Operation, loginSQL)
	SELECT d.ID, d.Year, 'DELETE', SYSTEM_USER
	FROM deleted d
END

CREATE TRIGGER TR_Update_Tracks
ON Tracks
FOR UPDATE
AS
BEGIN
	INSERT INTO LogTracks(TrackID, Name, Location, Length, NrOfCorners, AvgSpeed, Operation, loginSQL)
	SELECT d.ID, d.Name, d.Location, d.Length, d.NrOfCorners, d.AvgSpeed, 'UPDATE', SYSTEM_USER
	FROM deleted d
END

CREATE TRIGGER TR_Delete_Tracks
ON Tracks
FOR DELETE
AS
BEGIN
	INSERT INTO LogTracks(TrackID, Name, Location, Length, NrOfCorners, AvgSpeed, Operation, loginSQL)
	SELECT d.ID, d.Name, d.Location, d.Length, d.NrOfCorners, d.AvgSpeed, 'DELETE', SYSTEM_USER
	FROM deleted d
END

CREATE TRIGGER TR_Update_Races
ON Races
FOR UPDATE
AS
BEGIN
	INSERT INTO LogRaces(RaceID, CalendarID, TrackID, StartDate, EndDate, Operation, loginSQL)
	SELECT d.ID, d.CalendarID, d.TrackID, d.StartDate, d.EndDate, 'UPDATE', SYSTEM_USER
	FROM deleted d
END

CREATE TRIGGER TR_Delete_Races
ON Races
FOR DELETE
AS
BEGIN
	INSERT INTO LogRaces(RaceID, CalendarID, TrackID, StartDate, EndDate, Operation, loginSQL)
	SELECT d.ID, d.CalendarID, d.TrackID, d.StartDate, d.EndDate, 'DELETE', SYSTEM_USER
	FROM deleted d
END

-- Views
CREATE OR ALTER VIEW vw_ShowRaces AS
SELECT T.Name, C.Year, R.StartDate, R.EndDate
FROM Races R
JOIN Tracks T ON R.TrackID = T.ID
JOIN Calendars C ON R.CalendarID = C.ID

CREATE OR ALTER VIEW vw_LocationsTracksNr AS
SELECT Location, COUNT(*) AS Tracks
FROM Tracks
GROUP BY Location

-- Indexes
CREATE NONCLUSTERED INDEX idx_calendar_year
ON Calendars(Year)

CREATE NONCLUSTERED INDEX idx_track_name
ON Tracks(Name)

CREATE NONCLUSTERED INDEX idx_track_location
ON Tracks(Location)

-- ?
CREATE NONCLUSTERED INDEX idx_race_calendar
ON Races(CalendarID)