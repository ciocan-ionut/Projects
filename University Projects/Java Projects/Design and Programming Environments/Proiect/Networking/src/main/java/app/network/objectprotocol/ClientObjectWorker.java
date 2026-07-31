package app.network.objectprotocol;

import app.services.AppException;
import app.services.IObserver;
import app.services.IService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class ClientObjectWorker implements Runnable, IObserver {
    private final IService server;
    private final Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    private static final Logger logger = LogManager.getLogger(ClientObjectWorker.class);

    public ClientObjectWorker(IService server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (Exception e) {
            logger.error(e);
            logger.error(e.getStackTrace());
        }
    }

    @Override
    public void run() {
        while (connected) {
            try {
                Object request = input.readObject();
                Response response = handleRequest((Request) request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException e) {
                e.getStackTrace();
                connected = false;
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error " + e);
        }
    }

    @Override
    public void update() throws AppException {
        try {
            sendResponse(new TableUpdatedResponse());
        } catch (IOException e) {
            throw new AppException("Sending error " + e);
        }
    }

    private Response handleRequest(Request request) {
        if (request instanceof LoginRequest logReq) {
            try {
                server.login(logReq.getUsername(), logReq.getPassword(), this);
                return new OkResponse();
            } catch (AppException e) {
                connected = false;
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof LogoutRequest logReq) {
            try {
                server.logout(logReq.getUsername(), this);
                connected = false;
                return new OkResponse();
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof GetAllSwimmingTestsRequest) {
            try {
                return new GetAllSwimmingTestsResponse(server.getAllSwimmingTestDTOs());
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof GetSwimmingTestsForParticipantRequest req) {
            try {
                return new GetSwimmingTestsForParticipantResponse(server.getSwimmingTestsForParticipant(req.getParticipantId()));
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof GetParticipantsRequest req) {
            try {
                return new GetParticipantsResponse(server.getAllParticipantDTOs(req.getSwimmingTestId()));
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof AddParticipantRequest req) {
            try {
                server.addParticipant(req.getName(), req.getAge(), req.getTests());
                return new OkResponse();
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        if (request instanceof UpdateParticipantRequest req) {
            try {
                server.updateParticipant(req.getParticipantDTO(), req.getTests());
                return new OkResponse();
            } catch (AppException e) {
                return new ErrorResponse(e.getMessage());
            }
        }

        return null;
    }

    private void sendResponse(Response response) throws IOException {
        logger.debug("Sending response {}", response);
        synchronized (output) {
            output.writeObject(response);
            output.flush();
        }
    }
}
