/** Example2.java
 *  Approach 2: Creating threads by implementing interface Runnable.
 * IT 386 - Fall 2024
 *  * TODO:
 *   1. Implement run() method that prints current thread name
 *   2. Have main thread print current thread name
 *   3. Create and start  2 threads
  */
public class Activity13 implements Runnable {
  // 1. Implement run() method that prints current thread name
  @Override
  public void run(){
    System.out.println(Thread.currentThread().getName() + " is my name! Don't wear it out! (Why did I write this in this way?)");
  }
  public static void main(String[] args) throws InterruptedException {
    // 2.  Main thread print current thread name
   System.out.println("Hi! I'm " + Thread.currentThread().getName());
   int nThread = Integer.parseInt(args[0]);

   Thread[] worker = new Thread[nThread];
    // 3. Create and start 2 threads
    Runnable obj = new Activity13();
    for(int i = 0; i < nThread; i++){
      worker[i] = new Thread(obj);
      worker[i].start();
    }
    for(int i = 0; i < nThread; i++){
      worker[i].join();
    }

  }

}
