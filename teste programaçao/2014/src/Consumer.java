import java.io.*;
import java.net.*;
import java.lang.*;
public class Consumer {

    private MulticastSocket skt;
    private DatagramPacket pkt;
    private InetAddress group;
    private byte[] buf = new byte[1024];

    public static void main(String args[]){
        new Consumer(args[0], Integer.parseInt(args[1]));
    }

    public Consumer(String addr, int port){
        try {
            skt = new MulticastSocket(port);
            group = InetAddress.getByName(addr);
            skt.joinGroup(group);

            System.out.println("waiting for producer...");
            while (true) {
                pkt = new DatagramPacket(buf, buf.length);

                skt.receive(pkt);
                String received = new String(pkt.getData(), 0, pkt.getLength());

                System.out.println("data received: " + received);
            }
           // skt.leaveGroup(group);
           // skt.close();
        }
        catch(IOException e){
            System.out.println(e);
        }


    }


}
