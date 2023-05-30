package TCP.java.main;

import TCP.java.socket.Server;

public class StartServer {

    public static void main(String[] args) {
        Server server = new Server(10951);
        server.start();
    }
}