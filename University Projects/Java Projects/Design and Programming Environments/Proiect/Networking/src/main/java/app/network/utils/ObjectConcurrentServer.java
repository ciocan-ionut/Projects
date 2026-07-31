package app.network.utils;

import app.network.objectprotocol.ClientObjectWorker;
import app.services.IService;

import java.net.Socket;

public class ObjectConcurrentServer extends AbsConcurrentServer {
    private final IService service;

    public ObjectConcurrentServer(int port, IService service) {
        super(port);
        this.service = service;
    }

    @Override
    protected Thread createWorker(Socket socket) {
        ClientObjectWorker worker = new ClientObjectWorker(service, socket);
        return new Thread(worker);
    }
}
