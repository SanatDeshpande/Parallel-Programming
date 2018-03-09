import java.util.Random;

public class CoinFlip implements Runnable {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: CoinFlip #threads #iterations");
        } else {
            int threads = Integer.parseInt(args[0]);
            int iterations = Integer.parseInt(args[1]);
            CoinFlip[] coins = new CoinFlip[threads];
            Thread[] coinThreads = new Thread[threads];

            long start = System.currentTimeMillis();

            for (int i = 0; i < threads; i++) {
                coins[i] = new CoinFlip(threads, iterations);
                coinThreads[i] = new Thread(coins[i]);
                coinThreads[i].start();
            }

            int totalHeads = 0;

            // Await the completion of all threads
            for (int i=0; i<threads; i++) {
                try {
                    coinThreads[i].join();
                    totalHeads += coins[i].heads;
                } catch (InterruptedException e) {
                    System.out.println("Thread interrupted.  Exception: " + e.toString() +
                                   " Message: " + e.getMessage()) ;
                    return;
                }
            }
            long end = System.currentTimeMillis();
            System.out.println(totalHeads + " heads in " + iterations + " coin tosses");
            System.out.println("Elapsed Time: " + (end-start) + "ms");
        }
    }

    public static int threads;
    public static int iterations;

    public int heads;
    private Random rand;

    public CoinFlip(int threads, int iterations) {
        this.threads = threads;
        this.iterations = iterations;
        this.heads = 0;
        this.rand = new Random();
    }

    public void run() {
        for (int i = 0; i < iterations/threads; i++) {
            this.heads += rand.nextInt(2);
        }
    }
}
