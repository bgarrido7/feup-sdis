//HOW TO COMPILE & RUN
//javac *.java && java Client localhost 5000

import java.io.*;
import java.net.*;
import java.lang.*;

public class Client {
    private Socket skt;
    private DataInputStream in;
    private DataOutputStream out;

    public static void main(String args[]){
        Client client = new Client(args[0], Integer.parseInt(args[1]));
    }

    public Client(String addr, int port){
        try {
            skt = new Socket(addr, port);

            out = new DataOutputStream(skt.getOutputStream());
            in = new DataInputStream(skt.getInputStream());
//          in = new DataInputStream(new BufferedInputStream(skt.getInputStream()));

            out.writeUTF("AVG");
            System.out.println("message sent: AVG");

           float avg = in.readFloat();
           System.out.println("message received: " + avg);

            //manda 1 msg e depois de receber fecha socket
            in.close();
            out.close();
            skt.close();
        }
        catch(IOException e){
            System.out.println(e);
            System.exit(1);
        }
    }
}
