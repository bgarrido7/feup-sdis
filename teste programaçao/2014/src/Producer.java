import java.io.*;
import java.net.*;
import java.util.ArrayList;

class Producer{
    private InetAddress addr;
    private DatagramSocket skt;
    private DatagramPacket pkt;
    byte[] sendData = new byte[1024];

    public static void main(String args[]){

        ArrayList<Float> val = new ArrayList<Float>();

        for(int i=2; i<args.length; i++)
            val.add(Float.parseFloat( args[i]) );

        new Producer(args[0], Integer.parseInt(args[1]), val);
    }

    public Producer(String adress, int port, ArrayList<Float> val){
       
       try{
            
            skt = new DatagramSocket();

            for(int i=0; i<val.size(); i++){
                sendData = String.valueOf(val.get(i)).getBytes();
                
                addr = InetAddress.getByName(adress);
                pkt = new DatagramPacket(sendData, sendData.length, addr, port);
                
                skt.send(pkt);
                System.out.println("sent data: " + val.get(i));
                Thread.sleep(1000);
            }

        }
    
        catch(IOException | InterruptedException e){
            System.out.println(e);
        }
    
    
    }


}

