/**
 * @file Client.java
 * @brief Ce fichier contient la classe Client, qui représente un client se connectant à un serveur distant.
 */

import java.io.*;
import java.net.*;

/**
 * @brief Cette classe représente un client qui se connecte à un serveur distant.
 */

public class Client {
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3331;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;

    /**
     * @brief Constructeur de la classe Client.
     * @param host L'hôte du serveur distant.
     * @param port Le port du serveur distant.
     * @throws UnknownHostException Si l'hôte est inconnu.
     * @throws IOException En cas d'erreur d'entrée/sortie lors de la création du socket.
     */
    public Client(String host, int port) throws UnknownHostException, IOException {
        sock = new java.net.Socket(host, port);
        input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
    }

    /**
     * @brief Envoie une requête au serveur distant.
     * @param request La requête à envoyer.
     * @return La réponse du serveur distant.
     * @throws IOException En cas d'erreur d'entrée/sortie lors de l'envoi ou de la réception de la requête.
     */
    public String send(String request)throws IOException {
        try {
            request += "\n";
            output.write(request, 0, request.length());
            output.flush();
        } catch (IOException e) {
            System.err.println("Client: Couldn't send message: " + e);
            return null;
        }

        try {
            return input.readLine();
        } catch (IOException e) {
            System.err.println("Client: Couldn't receive message: " + e);
            return null;
        }
    }
}