// ─────────────────────────────────────────
//  CONCURRENCY
//  (Thread, Runnable, synchronized, volatile,
//   ExecutorService, Future, CompletableFuture)
// ─────────────────────────────────────────

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.concurrent.locks.*;

public class Concurrency {
    public static void main(String[] args) throws InterruptedException, ExecutionException {

        // ════════════════════════════════════
        //  CREATING THREADS
        // ════════════════════════════════════

        // 1) Extend Thread
        Thread t1 = new Thread() {
            @Override public void run() {
                System.out.println("Thread subclass: " + Thread.currentThread().getName());
            }
        };

        // 2) Implement Runnable (preferred — keeps task separate from thread)
        Runnable task = () -> System.out.println("Runnable lambda: " + Thread.currentThread().getName());
        Thread t2 = new Thread(task, "my-thread");

        t1.start();   // start() launches new thread — DON'T call run() directly
        t2.start();

        t1.join();    // wait for t1 to finish before continuing
        t2.join();

        // ── Thread info ───────────────────────────
        Thread me = Thread.currentThread();
        System.out.println("Name: "     + me.getName());
        System.out.println("Priority: " + me.getPriority());   // 1–10, default 5
        System.out.println("Daemon: "   + me.isDaemon());      // daemon threads stop when main exits

        // ── sleep ─────────────────────────────────
        // Thread.sleep(100);   // pause 100ms — throws InterruptedException

        // ════════════════════════════════════
        //  RACE CONDITION & synchronized
        // ════════════════════════════════════

        // Unsafe counter — multiple threads may corrupt it
        class UnsafeCounter {
            int count = 0;
            void increment() { count++; }   // not atomic!
        }

        // Safe counter — synchronized method
        class SafeCounter {
            private int count = 0;
            synchronized void increment() { count++; }   // only one thread at a time
            synchronized int  get()       { return count; }
        }

        SafeCounter counter = new SafeCounter();
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            Thread t = new Thread(counter::increment);
            threads.add(t);
            t.start();
        }
        for (Thread t : threads) t.join();
        System.out.println("Safe count: " + counter.get());   // always 1000

        // synchronized block — finer-grained (lock only part of the method)
        class BlockCounter {
            private int count = 0;
            private final Object lock = new Object();
            void increment() {
                synchronized (lock) {
                    count++;
                }
            }
        }

        // ── volatile — visibility guarantee across threads ─
        // volatile doesn't make compound ops (count++) atomic,
        // but ensures reads/writes are not cached in CPU registers.
        class FlagExample {
            volatile boolean running = true;
        }

        // ════════════════════════════════════
        //  ATOMIC VARIABLES
        // ════════════════════════════════════
        // Lock-free thread-safe operations

        AtomicInteger atomicCount = new AtomicInteger(0);
        List<Thread> atomicThreads = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            atomicThreads.add(new Thread(atomicCount::incrementAndGet));
        }
        atomicThreads.forEach(Thread::start);
        for (Thread t : atomicThreads) t.join();
        System.out.println("Atomic count: " + atomicCount.get());   // 1000

        atomicCount.set(10);
        atomicCount.addAndGet(5);       // 15
        atomicCount.compareAndSet(15, 99);  // if current==15, set to 99
        System.out.println(atomicCount.get());   // 99

        AtomicBoolean flag     = new AtomicBoolean(false);
        AtomicLong    longVal  = new AtomicLong(0L);
        AtomicReference<String> ref = new AtomicReference<>("hello");

        // ════════════════════════════════════
        //  LOCKS (java.util.concurrent.locks)
        // ════════════════════════════════════

        ReentrantLock lock = new ReentrantLock();
        int[] sharedVal = {0};

        Runnable lockedTask = () -> {
            lock.lock();
            try {
                sharedVal[0]++;
            } finally {
                lock.unlock();   // ALWAYS unlock in finally!
            }
        };

        // tryLock — non-blocking attempt
        if (lock.tryLock()) {
            try { sharedVal[0]++; }
            finally { lock.unlock(); }
        }

        // ReadWriteLock — multiple readers OR one writer at a time
        ReadWriteLock rwLock = new ReentrantReadWriteLock();
        rwLock.readLock().lock();
        // ... read shared data ...
        rwLock.readLock().unlock();

        // ════════════════════════════════════
        //  EXECUTOR SERVICE
        //  (thread pool — don't create raw Threads in real code)
        // ════════════════════════════════════

        // Fixed thread pool — reuses N threads
        ExecutorService pool = Executors.newFixedThreadPool(4);

        for (int i = 0; i < 8; i++) {
            final int id = i;
            pool.submit(() -> {
                System.out.println("Task " + id + " on " + Thread.currentThread().getName());
            });
        }

        // Callable<T> — like Runnable but returns a result
        Callable<Integer> computation = () -> {
            Thread.sleep(50);
            return 42;
        };

        Future<Integer> future = pool.submit(computation);
        System.out.println("Result: " + future.get());   // blocks until done

        // isDone / cancel
        Future<Integer> f2 = pool.submit(() -> { Thread.sleep(5000); return 1; });
        f2.cancel(true);   // interrupt the running task
        System.out.println("Cancelled: " + f2.isCancelled());

        pool.shutdown();                          // stop accepting new tasks
        pool.awaitTermination(5, TimeUnit.SECONDS); // wait for running tasks

        // Other executors:
        // Executors.newSingleThreadExecutor() — 1 thread, tasks queue up
        // Executors.newCachedThreadPool()     — grows/shrinks as needed
        // Executors.newScheduledThreadPool(n) — for delayed/periodic tasks

        // ════════════════════════════════════
        //  COMPLETABLE FUTURE (Java 8+)
        //  Async pipeline — no blocking required
        // ════════════════════════════════════

        // Run async, ignore result
        CompletableFuture.runAsync(() ->
            System.out.println("Async runnable on: " + Thread.currentThread().getName())
        );

        // Supply a value asynchronously
        CompletableFuture<String> cf = CompletableFuture.supplyAsync(() -> {
            return "hello";
        });

        // Chain transformations (non-blocking)
        CompletableFuture<Integer> pipeline = CompletableFuture
            .supplyAsync(() -> "hello world")
            .thenApply(s -> s.toUpperCase())          // transform result
            .thenApply(String::length);               // 11

        System.out.println("Pipeline: " + pipeline.get());

        // thenAccept — consume result (returns void)
        CompletableFuture.supplyAsync(() -> 42)
            .thenAccept(n -> System.out.println("Got: " + n));

        // thenCombine — combine two independent futures
        CompletableFuture<Integer> a = CompletableFuture.supplyAsync(() -> 10);
        CompletableFuture<Integer> b = CompletableFuture.supplyAsync(() -> 20);
        CompletableFuture<Integer> sum = a.thenCombine(b, Integer::sum);
        System.out.println("Combined: " + sum.get());   // 30

        // allOf — wait for all to finish
        CompletableFuture<Void> all = CompletableFuture.allOf(a, b);
        all.join();

        // anyOf — result of whichever finishes first
        CompletableFuture<Object> any = CompletableFuture.anyOf(a, b);
        System.out.println("First done: " + any.get());

        // Exception handling
        CompletableFuture<Integer> risky = CompletableFuture
            .supplyAsync(() -> { throw new RuntimeException("oops"); })
            .exceptionally(ex -> { System.out.println("Caught: " + ex.getMessage()); return -1; });
        System.out.println("Recovered: " + risky.get());   // -1

        CompletableFuture<Integer> handled = CompletableFuture
            .supplyAsync(() -> 5)
            .handle((result, ex) -> ex != null ? -1 : result * 2);  // handle both
        System.out.println("Handled: " + handled.get());   // 10

        // ════════════════════════════════════
        //  CONCURRENT COLLECTIONS
        // ════════════════════════════════════

        // ConcurrentHashMap — thread-safe HashMap (no global lock)
        ConcurrentHashMap<String, Integer> concMap = new ConcurrentHashMap<>();
        concMap.put("a", 1);
        concMap.putIfAbsent("b", 2);
        concMap.computeIfAbsent("c", k -> k.length());  // "c" → 1
        System.out.println(concMap);

        // CopyOnWriteArrayList — reads are lock-free; writes copy the array
        CopyOnWriteArrayList<String> cowList = new CopyOnWriteArrayList<>();
        cowList.add("x");
        cowList.add("y");

        // BlockingQueue — producer-consumer pattern
        BlockingQueue<String> queue = new LinkedBlockingQueue<>(10);
        queue.put("task1");               // blocks if full
        String item = queue.take();       // blocks if empty
        System.out.println("Took: " + item);

        // ════════════════════════════════════
        //  COMMON PITFALLS
        // ════════════════════════════════════
        // 1. Deadlock: T1 holds lock A, waits for B; T2 holds B, waits for A
        //    Fix: always acquire locks in the same order
        //
        // 2. Race condition: output depends on thread timing
        //    Fix: synchronize, use Atomic classes, or immutable data
        //
        // 3. Calling blocking get() on the main thread defeats async purpose
        //    Fix: chain callbacks with thenApply/thenAccept
        //
        // 4. Not shutting down ExecutorService causes JVM not to exit
        //    Fix: always call shutdown() or use try-with-resources (Java 19+)
    }
}
