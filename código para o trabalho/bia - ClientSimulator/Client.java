//HOW TO COMPILE & RUN:
//javac *.java && java Client nRequests

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class Client {
    private static int port = 5000;
    private static String addr ="127.0.0.1";

    List<Socket> skt = new ArrayList<>();
    List<DataOutputStream> out = new ArrayList<>();
    List<DataInputStream> in = new ArrayList<>();

    DataOutputStream o;
    DataInputStream inp;

    public static void main(String args[]){

        new Client( Integer.parseInt(args[0]) );
    }

    public Client(int nRequests){
        try{
            for(int i=0; i<=nRequests; i++){
                
                Socket socket = new Socket(addr, port);
                skt.add(socket);

                o = new DataOutputStream(skt.get(i).getOutputStream());
                out.add(o);
                inp = new DataInputStream(new BufferedInputStream(skt.get(i).getInputStream()));
                in.add(inp);

                if( i == nRequests )
                   out.get(i).writeUTF("EXIT");
                else {
                    System.out.println("Sending request to Socket Server " + i);
                    out.get(i).writeUTF(String.valueOf(i));
                }
            }

            for(int i=0; i<=nRequests; i++) {

                if(i == nRequests)
                    System.out.println("All clients have been answered");
                else{
                    String msg = in.get(i).readUTF();
                    System.out.println("Message Received: " + msg);

                    skt.get(i).close();
                    in.get(i).close();
                    out.get(i).close();
                }
            }

        }
        catch(IOException e) {
            System.out.println(e);
        }
    }
}


