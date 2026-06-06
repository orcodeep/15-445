```cpp
std::mutex mtx; // The mutex is CREATED here. (It is currently unlocked).

void safe_function() {
    
    // The scoped_lock is constructed right here.
    // The constructor immediately calls mtx.lock() behind the scenes!
    std::scoped_lock lock(mtx); // ofc it has internal checks to see if mutex
                                // is currently locked before acquiring it
    
    // Critical Section: Shared memory operations happen here...
    
} // 3. RELEASED: The function ends, 'lock' goes out of scope and is destructed.
  //    The destructor immediately calls mtx.unlock() behind the scenes!
```
`std::scoped_lock` was introduced in C++17 specifically to solve the exact circular-dependency deadlock scenario we talked about earlier **(where Thread 1 locks A and waits for B, while Thread 2 locks B and waits for A).**

```cpp
std::mutex mtx_A;
std::mutex mtx_B;

void safe_transfer() {
    // Pass BOTH mutexes into a single scoped_lock
    std::scoped_lock lock(mtx_A, mtx_B); 
    
    // Critical Section: Safe to interact with both A and B!
}
```
**How it avoids deadlocks under the hood:**

If you pass multiple mutexes into `std::scoped_lock`, it doesn't just lock them blindly from left to right. Instead, it uses a clever deadlock-avoidance algorithm (similar to `std::lock`).

If it tries to lock `mtx_A` and `mtx_B`, but realizes another thread is already holding `mtx_B`, it will actually release `mtx_A` back to the pool and try again. It guarantees an "**all-or-nothing**" execution. A thread will only move past that line if it successfully acquires every single lock passed into it simultaneously.


| Feature | std::scoped_lock | std::unique_lock |
|---|---|---|
| No. of<br>Mutexes | Multiple<br>(1 or more) | strictly one |
| Deadlock <br>Avoidance | Built-in<br>(when locking<br>multiple mutexes) | None<br>(must manage<br>lock order<br>manually) |
| Condition<br>Variable<br>Support | No | Yes <br>**std::condition_variable** <br>**strictly and exclusively** <br>**works with** <br>**std::unique_lock\<std::mutex\>** |
| Manual<br>Lock/Unlock | No | Yes (lock.unlock(), lock.lock()) |
| Transferable Ownership | No | Yes (Can be moved via<br>std::move) 



