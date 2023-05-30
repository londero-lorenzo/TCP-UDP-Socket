package TCP.java.socket;
// package nel quale è situata la classe Client TCP


/*
----Importazioni per il funzionamento della comunicazione TCP lato client----
 */

import java.io.IOException;
// importazione della classe generica invocata ogni qualvolta che si generi un problema input/output
import java.io.PrintWriter;
// importazione della classe per la scrittura sul flusso di dati in uscita dal socket
import java.net.Socket;
// importazione della classe socket
import java.util.NoSuchElementException;
// importazione della classe invocata ogni qualvolta che non viene trovata una linea successiva nel
//  flusso di dati in ricezione dal server
import java.util.Scanner;
// importazione della classe utilizzata per scrivere tramite la tastiera sulla console

public class Client {

    public void startClient(String ip, int port) {
        try {
            Socket socket = new Socket(ip, port);
            System.out.println("Connection established");
            System.out.println("Type a text:");
            Scanner socketIn = new Scanner(socket.getInputStream());
            PrintWriter socketOut = new PrintWriter(socket.getOutputStream());
            Scanner stdin = new Scanner(System.in);
            try {
                while (true) {
                    String inputLine = stdin.nextLine();
                    socketOut.println(inputLine);
                    socketOut.flush();
                    String socketLine = socketIn.nextLine();
                    System.out.println(socketLine);
                }
            } catch (NoSuchElementException ignored) {
            } finally {
                stdin.close();
                socketIn.close();
                socketOut.close();
                socket.close();
            }

        } catch (IOException ignored) {
        }
        System.out.println("Connection closed");
    }
}
