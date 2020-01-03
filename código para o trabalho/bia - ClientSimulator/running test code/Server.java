//HOW TO COMPILE & RUN:
//javac *.java && java Server


import java.io.*;
import java.net.*;

public class Server {

    private static int port = 5000;

    private ServerSocket ss;
    private Socket srv;
    private InputStream in;
    private OutputStream out;
    private String currentDirectory = System.getProperty("user.dir");

    public static void main(String args[]){
        new Server();
    }

    public Server(){
        try {
            int i=0;
            ss = new ServerSocket(port);
            System.out.println("Waiting for the client request...");
            File file = new File(currentDirectory + "/file/pp-2015.pdf");

            while(true){
                 //só para teste
                Thread.sleep(3000); //espera 3s

                Socket srv = ss.accept();
                in = new FileInputStream(file);
                out = srv.getOutputStream();

                byte[] bytes = new byte[16*1024];
                int count;
                while ((count = in.read(bytes)) > 0) {
                    out.write(bytes, 0, count);
                }
                System.out.println("file sent!");
                in.close();
                out.close();
                srv.close();
            }
         //   System.out.println("Shutting down Socket server!!");
         //   ss.close();

        }
        catch(IOException | InterruptedException e) {
            System.out.println(e);
            System.exit(1);
        }

    }
}