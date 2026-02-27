INSERT INTO TeamPrincipals(Name, Salary, ContractExpDate)
VALUES('Toto Wolff', 200000000, '2030-12-31');

INSERT INTO TeamPrincipals(Name, Salary, ContractExpDate)
VALUES('Fred Vasseur', 20000000, '2026-12-31');

INSERT INTO TeamPrincipals(Name, Salary, ContractExpDate)
VALUES('Christian Horner', 15000000, '2029-12-31');

INSERT INTO TeamPrincipals(Name, Salary, ContractExpDate)
VALUES('Andrea Stella', 10000000, '2027-12-31');

INSERT INTO Teams(Name, Budget, Location, TPID)
VALUES('Mercedes', 500000000, 'UK', 1);

INSERT INTO Teams(Name, Budget, Location, TPID)
VALUES('Ferrari', 450000000, 'Italy', 2);

INSERT INTO Teams(Name, Budget, Location, TPID)
VALUES('Red Bull', 480000000, 'Austria', 3);

INSERT INTO Teams(Name, Budget, Location, TPID)
VALUES('McLaren', 400000000, 'UK', 4);

INSERT INTO Cars(Number, Engine, HP, TeamID)
VALUES(16, 'Ferrari', 1000, 2);

INSERT INTO Cars(Number, Engine, HP, TeamID)
VALUES(44, 'Ferrari', 1020, 2);

INSERT INTO Cars(Number, Engine, HP, TeamID)
VALUES(63, 'Mercedes', 1010, 1);

INSERT INTO Cars(Number, Engine, HP, TeamID)
VALUES(1, 'Honda', 1040, 3);

INSERT INTO Cars(Number, Engine, HP, TeamID)
VALUES(4, 'Mercedes', 980, 4);

INSERT INTO Drivers(Name, Salary, ContractExpDate, TeamID, CarID)
VALUES('Charles Leclerc', 50000000, '2028-12-31', 2, 1); 

INSERT INTO Drivers(Name, Salary, ContractExpDate, TeamID, CarID)
VALUES('Lewis Hamilton', 55000000, '2028-12-31', 2, 2);

INSERT INTO Drivers(Name, Salary, ContractExpDate, TeamID, CarID)
VALUES('George Russell', 12000000, '2026-12-31', 1, 3);

INSERT INTO Drivers(Name, Salary, ContractExpDate, TeamID, CarID)
VALUES('Max Verstappen', 55000000, '2028-12-31', 3, 4);

INSERT INTO Drivers(Name, Salary, ContractExpDate, TeamID, CarID)
VALUES('Lando Norris', 20000000, '2027-12-31', 4, 5);

INSERT INTO Calendars(Year) VALUES (2023);

INSERT INTO Calendars(Year) VALUES (2024);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Monza', 'Italy', 5.793, 11, 250);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Imola', 'Italy', 4.909, 19, 205);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Silverstone', 'UK', 5.891, 18, 230);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Monaco', 'Monaco', 3.337, 19, 160);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Circuit de Barcelona-Catalunya', 'Spain', 4.657, 16, 210);

INSERT INTO Tracks(Name, Location, Length, NrOfCorners, AvgSpeed)
VALUES ('Madring', 'Spain', 5.4, 22, 220);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Mike Elliott', 500000, '2026-12-31', 'Aero', 1);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Enrico Cardile', 600000, '2026-12-31', 'Chassis', 2);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Adrian Newey', 2000000, '2030-12-31', 'Design', 3);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Peter Prodromou', 400000, '2026-12-31', 'Aero', 4);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Loic Serra', 450000, '2027-12-31', 'Performance', 1);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Jarrod Murphy', 380000, '2026-06-30', 'Strategy', 1);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Anthony Davidson', 420000, '2027-09-30', 'Aero', 1);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Jock Clear', 550000, '2027-12-31', 'Aero', 2);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('David Sanchez', 650000, '2028-12-31', 'Aero', 2);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Simone Resta', 600000, '2027-05-31', 'Chassis', 2);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Pierre Waché', 1000000, '2029-12-31', 'Technical Director', 3);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Ben Waterhouse', 700000, '2027-12-31', 'Performance', 3);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Craig Skinner', 500000, '2028-03-15', 'Design', 3);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('James Key', 800000, '2028-12-31', 'Technical Director', 4);

INSERT INTO Engineers(Name, Salary, ContractExpDate, Department, TeamID)
VALUES('Peter Prodromou Jr.', 450000, '2026-11-30', 'Aero', 4);

INSERT INTO PitStops(CarID, EngineerID, Duration)
VALUES(1, 2, '00:00:03');

INSERT INTO PitStops(CarID, EngineerID, Duration)
VALUES(4, 3, '00:00:07');

INSERT INTO PitStops(CarID, EngineerID, Duration)
VALUES(5, 4, '00:00:02');

INSERT INTO PitStops(CarID, EngineerID, Duration)
VALUES(3, 1, '00:00:03');

INSERT INTO Races(CalendarID, TrackID, StartDate, EndDate)
VALUES(1, 1, '2023-09-01', '2023-09-03');  -- Monza 2023

INSERT INTO Races(CalendarID, TrackID, StartDate, EndDate)
VALUES(1, 2, '2023-07-07', '2023-07-09');  -- Silverstone 2023

INSERT INTO Races(CalendarID, TrackID, StartDate, EndDate)
VALUES(2, 3, '2024-05-24', '2024-05-26');  -- Monaco 2024

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(4, 1, 1);   -- Verstappen wins Monza 2023

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(1, 1, 2);   -- Leclerc 2nd

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(2, 1, 3);   -- Hamilton 3rd

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(4, 2, 1);   -- Verstappen wins Silverstone 2023

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(3, 2, 2);   -- Russell 2nd

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(1, 2, 3);   -- Leclerc 3rd

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(4, 3, 1);   -- Verstappen wins Monaco 2024

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(1, 3, 2);   -- Leclerc 2nd

INSERT INTO Podiums(DriverID, RaceID, Place)
VALUES(6, 3, 3);   -- Norris 3rd