CREATE TABLE DBVersion(
	Version INT NOT NULL
);

INSERT INTO DBVersion(Version) VALUES (0);

CREATE OR ALTER PROCEDURE SetVersion @TargetVersion INT 
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @CurrentVersion INT;
	SELECT @CurrentVersion = Version FROM DBVersion;

	IF (@TargetVersion < 0 OR @TargetVersion > 5)
	BEGIN
		RAISERROR('Versiune invalida!', 16, 1);
		RETURN;
	END

	IF (@CurrentVersion = @TargetVersion)
	BEGIN
		PRINT('Baza de date este deja la versiunea specificata!');
		RETURN;
	END

	BEGIN TRY
		BEGIN TRANSACTION;
		
		WHILE (@CurrentVersion < @TargetVersion)
		BEGIN
			SET @CurrentVersion = @CurrentVersion + 1;

			IF (@CurrentVersion = 1) EXEC ModifyColumnType;
			IF (@CurrentVersion = 2) EXEC AddDefaultConstraint;
			IF (@CurrentVersion = 3) EXEC AddNewTable;
			IF (@CurrentVersion = 4) EXEC AddNewColumn;
			IF (@CurrentVersion = 5) EXEC AddFK;
		END

		WHILE (@CurrentVersion > @TargetVersion)
		BEGIN
			IF (@CurrentVersion = 5) EXEC RemoveFK;
			IF (@CurrentVersion = 4) EXEC RemoveNewColumn;
			IF (@CurrentVersion = 3) EXEC RemoveNewTable;
			IF (@CurrentVersion = 2) EXEC RemoveDefaultConstraint;
			IF (@CurrentVersion = 1) EXEC RevertColumnChanges;

			SET @CurrentVersion = @CurrentVersion - 1;
		END

		UPDATE DBVersion SET Version = @TargetVersion;
		PRINT('Baza de date a fost actualizata la versiunea ' + CAST(@TargetVersion AS NVARCHAR(10)));
		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION
		DECLARE @ErrMsg NVARCHAR(2048) = ERROR_MESSAGE();
		RAISERROR('Eroare la migrare: %s', 16, 1, @ErrMsg);
	END CATCH
END;

EXEC SetVersion 2