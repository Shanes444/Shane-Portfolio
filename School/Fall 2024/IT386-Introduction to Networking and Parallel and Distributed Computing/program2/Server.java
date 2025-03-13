//Shane Stevens
//IT 386 Program2
//Server class

import java.io.*;
import java.rmi.Naming;
import java.rmi.server.*;

public class Server {
    public static void main(String args[]) {
        try {
            //checks if arguments are provided
            if (args.length != 1) {
                System.out.println("Usage: java Server <port number>");
                return;
            }
            int portNumber = Integer.parseInt(args[0]);

            ComputeImpl obj = new ComputeImpl("Computation is ready");

            Naming.rebind("//localhost:" + portNumber + "/Server", obj);
            System.out.println("The computation server is ready");
        }
        catch (Exception e) {
            System.out.println("Server failed: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
