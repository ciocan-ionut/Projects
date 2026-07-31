package app.network.objectprotocol;

import app.model.ParticipantDTO;
import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;
import app.services.AppException;
import app.services.IObserver;
import app.services.IService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServicesObjectProxy implements IService {
    private final String host;
    private final int port;

    private IObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private static final Logger logger = LogManager.getLogger(ServicesObjectProxy.class);

    private final BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    public ServicesObjectProxy(String host, int port) {
        this.host = host;
        this.port = port;

        qresponses = new LinkedBlockingQueue<>();
    }

    @Override
    public void login(String username, String password, IObserver client) throws AppException {
        initializeConnection();
        sendRequest(new LoginRequest(username, password));
        Response response = readResponse();
        if (response instanceof OkResponse) {
            this.client = client;
            return;
        }
        if (response instanceof ErrorResponse errorResponse) {
            closeConnection();
            throw new AppException(errorResponse.getMessage());
        }
    }

    @Override
    public void logout(String username, IObserver client) throws AppException {
        sendRequest(new LogoutRequest(username));
        Response response = readResponse();
        closeConnection();
        if (response instanceof ErrorResponse errorResponse) {
            throw new AppException(errorResponse.getMessage());
        }
    }

    @Override
    public List<SwimmingTestDTO> getAllSwimmingTestDTOs() throws AppException {
        sendRequest(new GetAllSwimmingTestsRequest());
        Response response = readResponse();
        if (response instanceof ErrorResponse errorResponse) {
            throw new AppException(errorResponse.getMessage());
        }
        return ((GetAllSwimmingTestsResponse) response).getSwimmingTestDTOs();
    }

    @Override
    public List<SwimmingTest> getSwimmingTestsForParticipant(Integer participantId) throws AppException {
        sendRequest(new GetSwimmingTestsForParticipantRequest(participantId));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new AppException(((ErrorResponse) response).getMessage());
        }
        return ((GetSwimmingTestsForParticipantResponse) response).getSwimmingTests();
    }

    @Override
    public List<ParticipantDTO> getAllParticipantDTOs(int swimmingTestId) throws AppException {
        sendRequest(new GetParticipantsRequest(swimmingTestId));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new AppException(((ErrorResponse) response).getMessage());
        }
        return ((GetParticipantsResponse) response).getParticipants();
    }

    @Override
    public void addParticipant(String name, int age, List<SwimmingTest> swimmingTests) throws AppException {
        sendRequest(new AddParticipantRequest(name, age, swimmingTests));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new AppException(((ErrorResponse) response).getMessage());
        }
    }

    @Override
    public void updateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests) throws AppException {
        sendRequest(new UpdateParticipantRequest(participantDTO, swimmingTests));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new AppException(((ErrorResponse) response).getMessage());
        }
    }

    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException e) {
            logger.error("Error closing connection", e);
        }
    }

    private void sendRequest(Request request) throws AppException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new AppException("Error sending object " + e);
        }
    }

    private Response readResponse() throws AppException {
        Response response = null;
        try {
            response = qresponses.take();
        } catch (InterruptedException e) {
            logger.error("Error receiving response", e);
        }
        return response;
    }

    private void initializeConnection() throws AppException {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startReader();
        } catch (IOException e) {
            logger.error("Error initializing connection", e);
        }
    }

    private void startReader() {
        Thread thread = new Thread(new ReaderThread());
        thread.start();
    }

    private void handleUpdate(UpdateResponse update) {
        if (update instanceof TableUpdatedResponse) {
            try {
                client.update();
            } catch (AppException e) {
                logger.error("Error handling update", e);
            }
        }
    }

    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    logger.debug("response received {}", response);
                    if (response instanceof UpdateResponse) {
                        handleUpdate((UpdateResponse) response);
                    } else {
                        try {
                            qresponses.put((Response) response);
                        } catch (InterruptedException e) {
                            logger.error(e);
                        }
                    }
                } catch (IOException | ClassNotFoundException e) {
                    logger.error("Error receiving response", e);
                }
            }
        }
    }
}
