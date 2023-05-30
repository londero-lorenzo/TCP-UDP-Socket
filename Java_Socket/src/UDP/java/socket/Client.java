package UDP.java.socket;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.util.Scanner;

import static UDP.java.functions.getData;

public class Client {

    public void startClient(String ip, int port) {
        try {

            Scanner stdin = new Scanner(System.in);
            try (DatagramSocket datagramSocket = new DatagramSocket()) {
                InetAddress address = InetAddress.getByAddress(this.addressByteFromIpString(ip));
                byte[] buffer;
                byte[] bufferReceive;
                DatagramPacket datagramPacketToSend;
                DatagramPacket datagramPacketToReceive;
                System.out.println("Type a text:");
                while (true) {
                    String inputLine = stdin.nextLine();
                    buffer = inputLine.getBytes();

                    datagramPacketToSend = new DatagramPacket(buffer, buffer.length, address, port);
                    datagramSocket.send(datagramPacketToSend);
                    if (inputLine.equals("quit"))
                        break;
                    bufferReceive = new byte[25565];
                    datagramPacketToReceive = new DatagramPacket(bufferReceive, bufferReceive.length);
                    datagramSocket.receive(datagramPacketToReceive);

                    System.out.println("Received: " + getData(bufferReceive));

                }
            }
        } catch (IOException ignored) {
        }
        System.out.println("Connection closed");
    }

    private byte[] addressByteFromIpString(String ip) {
        byte[] ipByte = new byte[4];
        for (int i = 0; i < 4; i++) {
            ipByte[i] = (byte) Integer.parseInt(ip.split("\\.")[i]);
        }
        return ipByte;
    }
}
