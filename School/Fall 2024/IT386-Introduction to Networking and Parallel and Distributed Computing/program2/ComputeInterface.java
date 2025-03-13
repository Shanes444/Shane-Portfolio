//Shane Stevens
//IT 386 Program2
//Remote interface for compute program

import java.rmi.*;

public interface ComputeInterface extends Remote{
    
    //adds two numbers together
    int addition(int first, int second) throws RemoteException;
    
    //subtracts two numbers
    int subtraction(int first, int second) throws RemoteException;
    
    //multiplies two numbers
    int multiplication(int first, int second) throws RemoteException;
    
    //divides two numbers
    double division(double first, double second) throws RemoteException;
    
    //finds the greatest common divisor of two integers
    int gcd(int first, int second) throws RemoteException;

    //finds the area of a circle
    double circleArea(double radius) throws RemoteException;
    
    //finds the area of a rectangle
    int rectangleArea(int height, int length) throws RemoteException;
}