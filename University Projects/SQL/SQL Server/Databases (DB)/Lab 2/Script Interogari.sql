-- Show which drivers are on a specific team
SELECT D.Name, T.Name AS Team
FROM Drivers D
JOIN Teams T ON D.TeamID = T.ID
WHERE T.Name = 'Ferrari'

-- Shows every driver with the number on his car
SELECT C.Number, D.Name
FROM Cars C
JOIN Drivers D ON C.ID = D.CarID

-- Show the name of a team's TP
SELECT T.Name AS Team, TP.Name AS TP
FROM TeamPrincipals TP
JOIN Teams T ON T.TPID = TP.ID
WHERE T.Name = 'Ferrari'

-- Show which cars are powered by a specific engine
SELECT Number, Engine, HP
FROM Cars
WHERE Engine = 'Mercedes'

-- Show how many engineers a team has working in different departments
SELECT E.Department, COUNT(E.ID) AS Nr_Of_Engineers
FROM Engineers E
JOIN Teams T ON E.TeamID = T.ID
WHERE T.Name = 'Red Bull'
GROUP BY E.Department

-- Show how many races were in a year
SELECT CD.Year, COUNT(R.ID) AS Nr_Of_Races
FROM Races R
JOIN Calendars CD ON R.CalendarID = CD.ID
WHERE CD.Year = 2023
GROUP BY CD.Year

-- Show the cars with the lowest average duration lost in pitlane
SELECT C.Number, AVG(DATEDIFF(SECOND, '00:00:00', PS.Duration)) AS Avg_PitStop_Time
FROM PitStops PS
JOIN Cars C ON PS.CarID = C.ID
GROUP BY C.Number
HAVING AVG(DATEDIFF(SECOND, '00:00:00', PS.Duration)) < 5
ORDER BY Avg_PitStop_Time ASC

-- Show the drivers that have more than 1 podium
SELECT D.Name, COUNT(*) AS Nr_Of_Podiums
FROM Podiums P
JOIN Drivers D ON P.DriverID = D.ID
GROUP BY D.Name
HAVING COUNT(*) > 1
ORDER BY Nr_Of_Podiums DESC

-- Show the track and the year of each race
SELECT T.Name, CD.Year
FROM Races R
JOIN Tracks T ON R.TrackID = T.ID
JOIN Calendars CD ON R.CalendarID = CD.ID

-- Show where drivers took each of their podiums
SELECT DISTINCT D.Name, T.Name, P.Place
FROM Podiums P
JOIN Drivers D ON P.DriverID = D.ID
JOIN Races R ON P.RaceID = R.ID
JOIN Tracks T ON R.TrackID = T.ID

-- Show the distinct locations of the tracks
SELECT DISTINCT Location
FROM Tracks

-- Show the distinct locations where the teams have the base of operations
SELECT DISTINCT Location
FROM Teams