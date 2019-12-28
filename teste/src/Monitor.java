//HOW TO COMPILE & RUN:
//cd project/src
//javac *.java && java ClassName arg1 arg2 ... argN

import java.lang.*;
import java.util.Timer;
import java.util.TimerTask;
import java.net.*;
import java.io.*;

public class Monitor {
    private Socket socket = null;
    private ServerSocket server = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;

    public Monitor(String addr, int port, int period, int timeout) {
        try {
            socket = new Socket(addr, port);
            System.out.println("Server started");
            System.out.println("Waiting for a client ...");
            System.out.println("Client accepted");
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            out = new DataOutputStream(socket.getOutputStream());

            Timer timer = new Timer();
            PingTask pingTask = new PingTask(timeout);
            timer.schedule(pingTask, 1, period);

            //System.out.println("Closing connection");
            //socket.close();
            //in.close();
        } catch (IOException i) {
            System.out.println(i);
        }
    }

    public static void main(String args[]) {
        Monitor monitor = new Monitor(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));
    }

    private class PingTask extends TimerTask{

        private int timeout;
        PingTask(int timeout){
            this.timeout = timeout;
        }

        @Override
        public void run() {
            try {
                out.writeUTF("PING");
                Thread.sleep(this.timeout);
                try {
                    String line = in.readUTF();
                    if (line.equals("ALIVE")){
                        System.out.println("READ: " + line);
                    }
                } catch (IOException i) {
                    System.out.println(i);
                }
            }
            catch(IOException | InterruptedException e){}
        }
    }
}
