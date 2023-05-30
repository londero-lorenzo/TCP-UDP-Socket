package TCP.java.main;

import TCP.java.socket.Client;

public class StartClient {
    public static void main(String[] args) {
        Client client = new Client();
        client.startClient("192.168.178.134", 10951);
    }

    //10.3.0.143
}
