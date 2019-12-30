//javac *.java && java Target 5000
import java.net.*;
import java.io.*;

public class Target {
    private ServerSocket ss;
    private Socket socket;
    private DataInputStream input;
    private DataOutputStream out;

    public static void main(String args[]) {
        Target target = new Target(Integer.parseInt(args[0]));
    }

    public Target(int port) {
        try {
            ss = new ServerSocket(port);
            socket = ss.accept();
            input = new DataInputStream(socket.getInputStream());
            out = new DataOutputStream(socket.getOutputStream());
        } catch (IOException i){
            System.out.println(i);
        }

        while(true){
            try {
                String line = input.readUTF();
                if (line.equals("PING")){
                    System.out.println("Received PING");
                    out.writeUTF("ALIVE");
                }
            } catch (IOException i) {
                System.out.println(i);
            }
        }
    }
}