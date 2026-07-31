package app.persistance.repository;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class DBUtils {
    private final Properties dbProps;

    private Connection instance;

    private static final Logger logger = LogManager.getLogger();

    public DBUtils(Properties dbProps) {
        this.dbProps = dbProps;
    }

    private Connection createNewConnection() {
        logger.traceEntry();

        String url = dbProps.getProperty("URL");
        logger.info("Trying to connect to database...: {}", url);
        Connection connection = null;
        try {
            connection = DriverManager.getConnection(url);
        } catch (SQLException e) {
            logger.error(e);
            System.out.println("Error getting connection " + e);
        }
        return connection;
    }

    public Connection getConnection() {
        logger.traceEntry();
        try {
            if (instance == null || instance.isClosed()) {
                instance = createNewConnection();
            }
        } catch (SQLException e) {
            logger.error(e);
            System.out.println("Error DB " + e);
        }
        logger.traceExit(instance);
        return instance;
    }

    public void closeConnection() {
        logger.traceEntry();
        try {
            if (instance != null && !instance.isClosed()) {
                instance.close();
                logger.info("Connection closed.");
            }
        } catch (SQLException e) {
            logger.error(e);
            System.out.println("Error closing connection " + e);
        }
        logger.traceExit();
    }
}
