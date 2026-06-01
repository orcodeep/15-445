```cpp
auto my_ptr = std::make_unique<Point>(1, 2);
```
Behind the scenes, the standard library handles it exactly like this:

- It calls new Point(1, 2), which allocates memory on the heap and returns a raw pointer (Point*).

- It takes that raw pointer and feeds it directly into std::unique_ptr's normal constructor.

Because a raw pointer (Point*) is being fed into the class, the compiler successfully matches it to the normal constructor.


```cpp
void process(std::unique_ptr<Point> p_local);

// At the call site:
process(std::move(my_ptr));
```
The function parameter p_local needs to be constructed. The compiler looks at the argument you are passing in.

- Is it a raw pointer (Point*)? No. * What is it? It is a std::unique_ptr<Point>&& (an rvalue reference to a smart pointer).

Because you are passing a smart pointer type, it cannot match the normal constructor (which is strictly expecting a raw pointer type). The only constructor inside the class that knows how to accept a smart pointer type is the Move Constructor.


