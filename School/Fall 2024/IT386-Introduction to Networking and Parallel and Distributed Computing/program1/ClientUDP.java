// written by: Ryan Pukacz (Server written by: Shane Stevens)
// This file allows the client to read a message, send it to the server via UDP, get a response, receive a modified message from the server, and display the result on the screen.

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class ClientUDP {
    public static void main(String[] args) {
        // Makes sure that the format is correct
        if (args.length != 2) {
            System.out.println("please put in this format: java ClientUDP <hostname> <port>");
            return;
        }

        String hostname = args[0];
        int port = Integer.parseInt(args[1]);

        try {
            // Creates a UDP socket to send data to the server
            DatagramSocket clientSocket = new DatagramSocket();
            InetAddress serverAddress = InetAddress.getByName(hostname);
            // Get message from user keyboard input
            Scanner scan = new Scanner(System.in);
            System.out.print("Enter a message: ");
            String intialMessage = scan.nextLine();
            // Send message to server
            byte[] sendData = intialMessage.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, port);
            clientSocket.send(sendPacket);
            // Buffer to receive response from server
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            // Receive response from server
            clientSocket.receive(receivePacket);
            String serverResponse = new String(receivePacket.getData(), 0, receivePacket.getLength());
            // Print modified message from server on screen
            System.out.println("Modified message from server: " + serverResponse);
            // Close socket
            clientSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}