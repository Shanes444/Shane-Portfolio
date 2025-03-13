//Shane Stevens
//IT 386 Program2
//Client class

import java.io.*;
import java.rmi.Naming;
import java.util.Scanner;

public class Client {
    public static void main (String[] args){
        try{
            //check if arguments are provided
            if (args.length != 1){
                System.out.println("Usage: java Client <port number>");
                return;
            }
            Scanner scan = new Scanner(System.in);
            //connects to server
            int portNumber = Integer.parseInt(args[0]);
            ComputeInterface remoteObj = (ComputeInterface) Naming.lookup("//localhost:"+portNumber+"/Server");

            //gets the numbers used for calculation
            System.out.print("Enter the first number: ");
            int first = scan.nextInt();
            System.out.print("Enter the second number: ");
            int second = scan.nextInt();

            //does all computation
            System.out.println(first + " + " + second + " = " + remoteObj.addition(first, second));
            System.out.println(first + " - " + second + " = " + remoteObj.subtraction(first, second));
            System.out.println(first + " * " + second + " = " + remoteObj.multiplication(first, second));
            System.out.println(first + " / " + second + " = " + remoteObj.division(first, second));
            System.out.println("Greatest common divisor of " + first + " and " + second + " is " + remoteObj.gcd(first, second));
            System.out.println("area of circle with radius " + first + " is " + remoteObj.circleArea(first));
            System.out.println("area of " + first + " X " + second + "rectangle is " + remoteObj.rectangleArea(first, second));

            scan.close();
        }
        
        catch (Exception e) {
            System.out.println("Client exception: " + e);
        }
    }
}
