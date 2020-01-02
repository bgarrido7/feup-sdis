//this is the client


import java.lang.*;
import java.io.*;
import java.net.*;
import java.util.*;

public class Monitor{

    private Socket mnt;
    private DataInputStream in;
    private DataOutputStream out;

    private Timer timer;

    public static void main(String args[]){
        Monitor monitor = new Monitor(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));
    }

    public Monitor(String addr, int port, int period, int timeout){
        try {
            mnt = new Socket(addr, port);

            in = new DataInputStream(new BufferedInputStream(mnt.getInputStream()) );
            out = new DataOutputStream(mnt.getOutputStream());

            timer = new Timer();
            RemindTask rmd = new RemindTask(timeout);
            timer.schedule(rmd, 0, period);
          //  mnt.setSoTimeout(timeout);
        }

        catch(IOException e){
            System.out.println(e);
            System.exit(1);
        }
    }
    private void terminate(){
        try {
            in.close();
            out.close();
            mnt.close();

            timer.cancel();
            timer.purge();
            //    System.exit(0);
        }
        catch (IOException e){
            System.out.println(e);
            System.exit(1);
        }
    }


    private class RemindTask extends TimerTask{

        private int timeout;
        RemindTask(int timeout){
            this.timeout=timeout;
        }

        @Override
        public void run() {
            try {
                out.writeUTF("ping");
                System.out.println("message sent: PING");

                Thread.sleep(this.timeout);
                String msg = in.readUTF();
                if (msg.equals("ALIVE")) {
                    System.out.println("Target ALIVE");
                } else
                    terminate();

            } catch (IOException | InterruptedException e) {
                terminate();
                System.out.println("FAULT: timeout exceeded");

            }
        }
    }
}
