import java.io.*;
import java.net.*;

public class Client {
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3331;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;


    public Client(String host, int port) throws UnknownHostException, IOException {
        sock = new java.net.Socket(host, port);
        input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
    }

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