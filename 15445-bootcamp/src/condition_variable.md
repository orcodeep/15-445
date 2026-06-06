# Remzi condidional variables notes

We make the cond variable a global one.
- In most standard C/C++ multithreaded programs, the condition variable (along with the mutex and the guard variable it protects) is made global.<br><br>**Because multiple different threads need to access the exact same condition variable to either sleep on it (wait) or wake others up (signal), it has to be defined in a scope that all those threads can see.**<br><br>While making them global is the easiest and most common approach for simple programs, global variables can get messy in large, production-grade codebases.<br>
The cleaner architectural alternative is to encapsulate them inside a struct (in C) or an object/class (in C++, Java, or Python), and then pass a pointer or reference to that object into the threads when you create them.

Under the hood, a condition variable is essentially a wrapper around a thread queue managed by the operating system kernel.

**when different threads are waiting for different states to occur then we shouldn't queue them in the same conditional variable**





