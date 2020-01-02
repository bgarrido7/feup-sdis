//HOW TO COMPILE & RUN:
//javac *.java && java Server


import java.io.*;
import java.net.*;

public class Server {
    private static int port = 5000;

    private ServerSocket ss;
    private Socket srv;
    private DataInputStream in;
    private DataOutputStream out;

    public static void main(String args[]){
        new Server();
    }

    public Server(){
        try {
            ss = new ServerSocket(port);
            System.out.println("Waiting for the client request...");
            while(true){
                //só para teste
                Thread.sleep(3000); //espera 3s

                Socket srv = ss.accept();
                in = new DataInputStream(srv.getInputStream());
                out = new DataOutputStream(srv.getOutputStream());

                String msg = in.readUTF();
                System.out.println("Message Received: " + msg);

                if(msg.equals("EXIT"))
                    break;
                else {
                    System.out.println("Message Sent: Hi Client " + msg);
                    out.writeUTF("Hi Client " + msg);
                    in.close();
                    out.close();
                    srv.close();
                }


            }
            System.out.println("Shutting down Socket server!!");
            ss.close();

        }
        catch(IOException | InterruptedException e) {
            System.out.println(e);
            System.exit(1);
        }

    }
}