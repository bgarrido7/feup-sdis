import java.net.*;
import java.io.*;



public class client {
    public static void main(String[] args) throws IOException {
        Socket socket = null;
        String host = "localhost";

        socket = new Socket(host, 4444);

        File file = new File("c:\\Testes\\Dance Music Manual.pdf");
        // Get the size of the file
        long length = file.length();
        byte[] bytes = new byte[16 * 1024];
        InputStream in = new FileInputStream(file);
        OutputStream out = socket.getOutputStream();

        int count;
        while ((count = in.read(bytes)) > 0) {
            out.write(bytes, 0, count);
        }

        out.close();
        in.close();
        socket.close();
    }
}