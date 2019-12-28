import java.net.*;
import java.io.*;

public class Target {
    private ServerSocket ss = null;
    private Socket socket;
    private DataInputStream input = null;
    private DataOutputStream out = null;

    public Target(int port) {
        try {
            ss = new ServerSocket(port);
            socket = ss.accept();
            System.out.println("Connected");
            input = new DataInputStream(socket.getInputStream());
            out = new DataOutputStream(socket.getOutputStream());
        } catch (IOException i){
            System.out.println(i);
        }

        while(true){
            try {
                String line = input.readUTF();
                if (line.equals("PING")){
                    System.out.println("READ: " + line);
                    out.writeUTF("ALIVE");
                }
            } catch (IOException i) {
                System.out.println(i);
            }
        }
        /*
        try {
            input.close();
            out.close();
            socket.close();
        } catch (IOException i) {
            System.out.println(i);
        }*/
    }

    public static void main(String args[]) {
        Target target = new Target(Integer.parseInt(args[0]));
    }
}