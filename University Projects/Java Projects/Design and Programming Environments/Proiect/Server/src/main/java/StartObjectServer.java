import app.network.utils.AbstractServer;
import app.network.utils.ObjectConcurrentServer;
import app.network.utils.ServerException;
import app.persistance.OrganizerRepository;
import app.persistance.ParticipantRepository;
import app.persistance.SwimmingTestRepository;
import app.persistance.hibernate.ParticipantsHibernateRepository;
import app.persistance.hibernate.SwimmingTestsHibernateRepository;
import app.persistance.repository.DBUtils;
import app.persistance.repository.OrganizersDBRepository;
import app.persistance.repository.ParticipantsDBRepository;
import app.persistance.repository.SwimmingTestsDBRepository;
import app.server.ProtoService;
import app.server.Service;
import app.services.IService;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.IOException;
import java.util.Properties;

public class StartObjectServer {
    private static final int PORT = 55555;

    private static final Logger logger = LogManager.getLogger(StartObjectServer.class);

    public static void main(String[] args) {
        Properties prop = new Properties();
        try {
            prop.load(StartObjectServer.class.getResourceAsStream("/bd.config"));
            logger.info("Server properties set. ");
            prop.list(System.out);
        } catch (IOException e) {
            logger.error("Cannot find chatserver.properties ", e);
            return;
        }

        SessionFactory sessionFactory = new Configuration().configure("hibernate.cfg.xml").buildSessionFactory();
        DBUtils dbUtils = new DBUtils(prop);
        OrganizerRepository organizerRepository = new OrganizersDBRepository(dbUtils);
        ParticipantRepository participantRepository = new ParticipantsHibernateRepository(sessionFactory);
        SwimmingTestRepository swimmingTestRepository = new SwimmingTestsHibernateRepository(sessionFactory);
        IService service = new Service(organizerRepository, participantRepository, swimmingTestRepository);

        ProtoService protoService = new ProtoService(service);

        try {
            Server server = ServerBuilder.forPort(PORT)
                    .addService(protoService)
                    .build()
                    .start();
            Runtime.getRuntime().addShutdownHook(new Thread(() -> {
                logger.info("Shutting down gRPC server...");
                server.shutdown();
                dbUtils.closeConnection();
                if (sessionFactory != null) {
                    sessionFactory.close();
                }
            }));
            logger.info("Server started, listening on {}", PORT);
            server.awaitTermination();
        } catch (Exception e) {
            logger.error("Error from the server: ", e);
        }


//        AbstractServer server = new ObjectConcurrentServer(PORT, service);
//        try {
//            server.start();
//        } catch (ServerException e) {
//            logger.error("Error starting the server: ", e);
//        } finally {
//            dbUtils.closeConnection();
//        }
    }
}
