
/**  File: ParallelSum.java
 *  A team of threads adds up the numbers of an array
 * Name:
 * Date:
 *          Activity 13
 * IT 386
  */
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

public class ParallelSum {
    // shared variables
    static int nThreads, N;
    static int arrayA[];
    static long totalSum=0;

    public static void main(String[] args) throws InterruptedException {
        //count start time
        long startTime = System.currentTimeMillis();
        if (args.length > 0) {
            nThreads = Integer.parseInt(args[0]);
            N = Integer.parseInt(args[1]);
        } else {
            System.out.println("Usage: java className <number of Threads> < N > ");
            System.exit(1);
        }

        arrayA = new int[N];
        for (int i = 0; i < N; i++) {
            arrayA[i] = i + 1;
        }
        /* Main thread prints initial array */
        if (N < 20) {
            System.out.println(Thread.currentThread().getName() + ": " + Arrays.toString(arrayA));
        }

        /* Create array to hold team of threads */
        Thread[] workers = new Thread[nThreads];
        int work = N / nThreads; // amount of work each thread will do
        int remainder = N%nThreads;
        for (int i = 0; i < nThreads; i++) {
            //add extra work to last thread
            int low = i * work;
            int high = (i + 1) * work;
            if(i ==nThreads - 1 && remainder != 0){
                high = N;
            }

            Runnable obj = new Worker(low, high);
            workers[i] = new Thread(obj);
            workers[i].start();
        }

        for (int i = 0; i < nThreads; i++) {
            workers[i].join();
        }
        //elapsed time
        long elapsed = System.currentTimeMillis() - startTime;

        System.out.println("N = " + N + "; nThreads = " + nThreads + " ellapsed time = " + elapsed + " msec");
        System.out.println("SeqSum " +seqSum() + ", Parallel Sum " + totalSum);


    } /* main */

    public static class Worker implements Runnable {
        // Create a new ReentrantLock 
        static ReentrantLock mutex = new ReentrantLock();
        private int low, high;
        private long localSum;
        public Worker(int low, int high) {
            this.low = low;
            this.high = high;
        }
        @Override
        public void run() {
            localSum = 0;
            for (int i = low; i < high; i++) {
                localSum += arrayA[i];
            }
            mutex.lock();
            try{
                totalSum += localSum; 
            }
            finally{
                mutex.unlock();
            }
            
        }
    }

    public static long seqSum() {
        long sum = 0;
        for (int i = 0; i < N; i++) {
            sum += arrayA[i];
        }
        return sum;
    }

}
