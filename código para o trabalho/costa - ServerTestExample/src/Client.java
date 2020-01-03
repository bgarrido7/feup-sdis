import java.io.*;
import java.net.*;

public class Client {
    private Socket skt;
    private InputStream in;
    private OutputStream out;
    private String currentDirectory = System.getProperty("user.dir");

    private String addr = "localhost";
    private int port = 5000;

    public static void main(String args[]) {
        Client client = new Client();
    }

    public Client() {
        try {
            skt = new Socket(addr, port);
            File file = new File(currentDirectory + "/receivedFile.pdf");

            long length = file.length();
            byte[] bytes = new byte[16 * 1024];
            in = skt.getInputStream();
            out = new FileOutputStream(file);

            int count;
            while ((count = in.read(bytes)) > 0) {
                out.write(bytes, 0, count);
            }
            System.out.println("file received!");

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

