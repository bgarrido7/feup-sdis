//HOW TO COMPILE & RUN
//javac *.java && java Server 5000 9.389

import java.io.*;
import java.net.*;

public class Server {
    private ServerSocket ss;
    private Socket srv;
    private DataInputStream in;
    private DataOutputStream out;

    public static void main(String args[]){
        Server srv = new Server(Integer.parseInt(args[0]), Float.parseFloat(args[1]));
    }

    public Server(int port, float average){
        try {
            ss = new ServerSocket(port);

            while(true) {
                System.out.println("waiting for client's request...");
                srv = ss.accept();

                in = new DataInputStream(srv.getInputStream());
                out = new DataOutputStream(srv.getOutputStream());

                String msg = in.readUTF();

                if(msg.equals("AVG")){
                    System.out.println("message received: AVG");
                    out.writeFloat(average);
                    System.out.println("Sent message: " + average);
                }
            }
        }
        catch(IOException e){
            System.out.println(e);
         //   out.close();
         //   ss.close();
            System.exit(1);
        }

    }
}
