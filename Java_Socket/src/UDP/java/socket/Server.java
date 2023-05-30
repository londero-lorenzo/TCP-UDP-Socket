package UDP.java.socket;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

import static UDP.java.functions.getData;

public class Server {

    public int port;

    public Server(int port) {
        this.port = port;
    }

    public void start() {
        try {
            DatagramSocket datagramSocket = new DatagramSocket(this.port);
            System.out.println("Server socket ready on port: " + this.port);
            byte[] bufferReceive;
            DatagramPacket datagramPacketToReceive;
            DatagramPacket datagramPacketToSend;

            while (true) {
                bufferReceive = new byte[25565];
                datagramPacketToReceive = new DatagramPacket(bufferReceive, bufferReceive.length);
                datagramSocket.receive(datagramPacketToReceive);
                if (getData(bufferReceive).equals("quit"))
                    break;
                InetAddress returnAddress = datagramPacketToReceive.getAddress();
                int returnPort = datagramPacketToReceive.getPort();
                datagramPacketToSend = new DatagramPacket(bufferReceive, bufferReceive.length, returnAddress, returnPort);
                datagramSocket.send(datagramPacketToSend);

            }
            datagramSocket.close();
        } catch (IOException ignored) {
        }
        System.out.println("Closing sockets");
        System.out.println("Connection closed");
    }
}