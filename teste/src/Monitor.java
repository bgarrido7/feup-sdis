//HOW TO COMPILE & RUN:
//cd project/src
//javac *.java && java ClassName arg1 arg2 ... argN
//javac *.java && java Monitor localhost 5000 3000 1000
import java.lang.*;
import java.util.*;
import java.net.*;
import java.io.*;

public class Monitor {
    private Socket socket;
    private DataInputStream in;
    private DataOutputStream out;
    private Timer timer;

    public static void main(String args[]) {
        Monitor monitor = new Monitor(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));
    }

    public Monitor(String addr, int port, int period, int timeout) {
        try {
            socket = new Socket(addr, port);
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            out = new DataOutputStream(socket.getOutputStream());
            timer = new Timer();
            PingTask pingTask = new PingTask(timeout);
            timer.schedule(pingTask, 1, period);
        } catch (IOException i) {
            System.out.println(i);
        }
    }

    void terminate() {
        System.out.println("Target status: TERMINATED");
        System.out.println("Stopping monitoring service");
        try {
            timer.cancel();
            timer.purge();
            socket.close();
            in.close();
            out.close();
        } catch(IOException e){
            System.out.println(e);
        }
    }

    private class PingTask extends TimerTask {

        private int timeout;

        PingTask(int timeout) {
            this.timeout = timeout;
        }

        @Override
        public void run() {
            try {
                out.writeUTF("PING");
                Thread.sleep(this.timeout);
                String line = in.readUTF();
                if (line.equals("ALIVE"))
                    System.out.println("Target status: " + line);
                else
                    terminate();
            } catch (IOException | InterruptedException e) {
                terminate();
            }
        }
    }
}
