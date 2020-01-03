import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.List;

public class Producer {

    private DatagramSocket skt;
    private DatagramPacket pkt;
    private InetAddress group;
    private byte[] buf;

    private float avg=0;
    private static float sum=0;

    public static void main(String args[]) {
        List<Float> val = new ArrayList<>();

        for (int i=2; i<args.length; i++) {
            val.add(Float.parseFloat(args[i]));
            sum+=Float.parseFloat(args[i]);
        }
        new Producer(args[0], Integer.parseInt(args[1]), val);
    }

    public Producer(String addr, int port, List<Float> val){

        avg = sum/val.size();
        try {
         //   Thread.sleep(1000);

            group = InetAddress.getByName(addr);
            skt = new DatagramSocket();

            avg = sum / val.size();
            buf = Float.toString(avg).getBytes();

            pkt = new DatagramPacket(buf, buf.length, group, port);

            skt.send(pkt);
            System.out.println("data sent!");

            skt.close();
        }
        catch(IOException /*| InterruptedException*/ e){
            System.out.println(e);
        }
    }

}
