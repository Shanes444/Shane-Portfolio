//written by: Shane Stevens (Client written by: Ryan Pukacz)
//This file takes incoming UDP messages and returns the message to the sender in UPPER CASE and adds the server name to it

import java.net.*;

class ServerUDP {
  public static void main (String[] args) throws Exception {

    //Gets port number
    if (args.length != 1) {
        System.err.println("Usage: java ServerTCP <port number>");
        System.exit(1);
     }

     int portNumber = Integer.parseInt(args[0]);

     boolean isRunning = true;
     byte[] receiveData = new byte[256];
     int count = 0;

    //creates socket
     DatagramSocket serverSocket = new DatagramSocket(portNumber);

     while(isRunning){
        //creates packet
        DatagramPacket recvPacket = new DatagramPacket(receiveData,receiveData.length);
        //recieves packet
        serverSocket.receive(recvPacket);
        //gets string from packet
        String receiveString = new String(recvPacket.getData(), 0, recvPacket.getLength());
        //I just added this so that there is a proper way to close the socket.
        //Theres probably a better way to do this
        if(receiveString.equals("0")){
            isRunning = false;
        }
        //modifies the string as specified in the instructions
        receiveString = receiveString.toUpperCase() + " " + InetAddress.getLocalHost().getHostName();
        byte[] returnByte = receiveString.getBytes();
        //prints message for server
        System.out.println("Message " + count + ": " + receiveString);
        count++;

        //creates packet that is sent back to client
        DatagramPacket returnPacket = new DatagramPacket(returnByte, returnByte.length, recvPacket.getSocketAddress());
        serverSocket.send(returnPacket);
     }
     //closes the socket
     serverSocket.close();
  }
}