1. When 100 threads IS pointless (CPU-Bound Tasks)

If your threads are doing pure calculation (e.g., calculating cryptography, rendering 3D graphics, or processing video) and your CPU has 32 threads:

- 32 Software Threads: Runs at maximum physical speed.(`Parralelism benefit`)

- 100 Software Threads: Runs slower than 32 threads.

Why? Because the CPU cores are already maxed out at 100% capacity with 32 threads. Adding 68 more threads doesn't give you more computing power; it just forces the CPU to constantly pause its work, save memory states, and swap threads in and out (context switching). You are paying a performance tax for absolutely no gain.
2. When 100 threads IS brilliant (I/O-Bound Tasks)

If your threads are spending most of their time waiting for the network, a database, or a hard drive:

- 32 Software Threads: You can only talk to 32 servers at a time. If you have to scrape 1,000 websites, you have to wait in line.

- 100 Software Threads (or more): You can kick off 100 web requests simultaneously. (`Concurrency benefit`)

Because 99% of a web request's time is spent just waiting for the data to travel across the internet, those threads take up almost zero CPU power while they wait. The CPU can easily manage all 100 requests at once. The moment Server #42 responds, that specific thread wakes up, the CPU processes the data in a fraction of a millisecond, and goes back to waiting. In this scenario, 100 threads makes your program finish drastically faster.


