import java.io.*;
import java.net.*;

class Consumer{
    private InetAddress group;

    private MulticastSocket skt;
    private DatagramPacket pkt;
    byte[] rcvData = new byte[1024];
    public static void main(String args[]){
        new Consumer(args[0], Integer.parseInt(args[1]));
    }

    public Consumer(String addr, int port){
         
        try{
            System.out.println("waiting for producer...");

            while(true){
                
                group = InetAddress.getByName(addr);
                skt = new MulticastSocket(port);
                skt.joinGroup(group);

                pkt = new DatagramPacket(rcvData, rcvData.length);
                
                skt.receive(pkt);
                String data = new String(pkt.getData());
                System.out.println("recieved data: " + data);
            }

        }
        catch(IOException e){
            System.out.println(e);
        }

    }


}
