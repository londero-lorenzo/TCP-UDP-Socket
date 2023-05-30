package TCP.java.socket;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {

    public int port;

    public Server(int port) {
        this.port = port;
    }

    public void start() {
        try {
            //apro una porta TCP
            ServerSocket serverSocket = new ServerSocket(this.port);
            System.out.println("Server socket ready on port: " + this.port);
            //resto in attesa di una connessione


            Socket socket = serverSocket.accept();
            System.out.println("Received client connection");
            //apro gli scream d'input e output per leggere e scrivere nella connessione appena ricevuta Scanner in=

            //InputStream in = socket.getInputStream();

            //leggo e scrivo nella connessione finchè non ricevo <quit>

            Scanner inputScanner;
            String lineWrote;
            PrintWriter outputSocketPrinter;
            do {
                inputScanner = new Scanner(socket.getInputStream());
                lineWrote = inputScanner.nextLine();
                outputSocketPrinter = new PrintWriter(socket.getOutputStream());
                outputSocketPrinter.println("Received: " + lineWrote);
                outputSocketPrinter.flush();
            } while (!lineWrote.equals("quit"));
            // chiudo gli stream e il socket
            socket.close();
        } catch (IOException ignored) {
        }
        System.out.println("Closing sockets");
        System.out.println("Connection closed");
    }
}