//this is the server

import java.io.*;
import java.net.*;

public class Target{
    private ServerSocket ss;
    private String msg;
    private Socket trg;
    private DataInputStream in;
    private DataOutputStream out;

    public static void main(String args[]){
        Target target=new Target(Integer.parseInt(args[0]));
    }

    public Target(int port){
        try {
            ss = new ServerSocket(port);

            trg = ss.accept();

            in = new DataInputStream(trg.getInputStream());
            out = new DataOutputStream(trg.getOutputStream());
        }
        catch(IOException i){
            System.out.println(i);
            System.exit(1);
        }
        while(true){
            try {
                msg = in.readUTF();

                if (msg.equals("ping")) {
                    System.out.println("message received: PING");
                    out.writeUTF("ALIVE");
                }
            }
            catch(IOException i){
                System.out.println(i);
                System.exit(1);
            }
        }

    }
}
