//HOW TO COMPILE & RUN:
//javac *.java && java Client nRequests

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class Client {
    private static int port = 5000;
    private static String addr ="127.0.0.1";
    private String currentDirectory = System.getProperty("user.dir");

    List<Socket> skt = new ArrayList<>();
    List<OutputStream> out = new ArrayList<>();
    List<InputStream> in = new ArrayList<>();

    public static void main(String args[]){
        new Client( Integer.parseInt(args[0]) );
    }

    public Client(int nRequests){
        try{
            for(int i=0; i<nRequests; i++){
                int n=i+1;
                Socket socket = new Socket(addr, port);
                skt.add(socket);

                in.add( skt.get(i).getInputStream() );
                out.add( new FileOutputStream(new File(currentDirectory + "/receivedFile" + n +".pdf")) );

                System.out.println("request sent for client " + n);
            }

            for(int i=0; i<nRequests; i++) {
                int n=i+1;
                byte[] bytes = new byte[16 * 1024];
                int count;
                while ((count = in.get(i).read(bytes)) > 0) {
                    out.get(i).write(bytes, 0, count);
                }
                System.out.println("file received for client " + n);

                skt.get(i).close();
                in.get(i).close();
                out.get(i).close();
            }

        }
        catch(IOException e) {
            System.out.println(e);
        }
    }
}


