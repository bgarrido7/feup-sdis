import java.io.*;
import java.net.*;

public class Server {
    private ServerSocket ss;
    private Socket srv;
    private InputStream in;
    private OutputStream out;
    private int port = 5000;

    private String currentDirectory = System.getProperty("user.dir");

    public static void main(String args[]){
        new Server();
    }

    public Server(){
        System.out.println("waiting for client's request...");
        try {
            File file = new File(currentDirectory + "/file/pp-2015.pdf");

            ss = new ServerSocket(port);
            srv = ss.accept();
            in = new FileInputStream(file);
            out = srv.getOutputStream();

            byte[] bytes = new byte[16*1024];
            int count;
            while ((count = in.read(bytes)) > 0) {
                out.write(bytes, 0, count);
            }
            System.out.println("file sent!");

            srv.close();
            out.close();
            in.close();
        }

        catch(IOException e){
            System.out.println(e);
            System.exit(1);
        }

    }
}
