//Shane Stevens
//IT386 Program2
//Implementation for remote interface

import java.rmi.*;
import java.rmi.server.*;

public class ComputeImpl extends UnicastRemoteObject implements ComputeInterface{
    private String message;

    //remote object constructor
    public ComputeImpl(String msg) throws RemoteException{
        message = msg;
    }

    //implementation of addition function
    public int addition(int first, int second) throws RemoteException{
        return first + second;
    }

    //implementation of subtraction function
    public int subtraction(int first, int second) throws RemoteException{
        return first - second;
    }

    //implementation of multiplication function
    public int multiplication(int first, int second) throws RemoteException{
        return first * second;
    }

    //implementation of division function
    public double division(double first, double second) throws RemoteException{
        return first / second;
    }
    
    //implementation of gcd function
    public int gcd(int first, int second) throws RemoteException{
        while(first != second){
            if(first > second)
                first = first - second;
            else
                second = second - first;
        }
        return first;
    }

    //implementation of circleArea function
    public double circleArea(double radius) throws RemoteException{
        return Math.PI * radius * radius;
    }

    //implementation of rectangleArea function
    public int rectangleArea(int height, int length){
        return height * length;
    }
}
