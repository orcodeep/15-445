`std::vector<int> stealing_ints = std::move(int_array);`

If you didn't use move: `std::vector<int> stealing_ints = int_array;`

- The RHS is an lvalue.
- The compiler calls the Copy Constructor.
- Result: A brand new array is allocated, and every number is copied.

you used move: `std::vector<int> stealing_ints = std::move(int_array);`

- The RHS is now an rvalue reference.
- The compiler calls the Move Constructor.
- Result: stealing_ints simply copies the internal pointer (the address of the data) from int_array

`std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);`

The name of an rvalue reference is an lvalue.

Here is the imp point, how the "lvalue-ness" of the name v acts as a safety barrier.
<pre>
void some_function(std::vector< int >&& incoming); // Wants an rvalue
{}

void process(std::vector< int >&& v) {
    // REALITY:
    some_function(v); // COMPILER ERROR!
}
</pre>

- some_function demands an rvalue (&&).
- v has a name, so the compiler treats it as an lvalue.
- You explicitly cast the name 'v' back into an rvalue `some_function(std::move(v));` that would work.<br><br>
But if the `some_function` doesnt explicitly move the `incoming` rvalue ref arg into a lvalue in its own context then `v` can still be used inside the caller function `process`.

When you do someting like `std::vector< int > array = std::move(prev_array);`, you are calling the Move Constructor of std::vector(not move assignment operator because here array is being born in place its not a object that already exists).

Because the developers of the C++ Standard Library already wrote the "stealing" logic inside the vector class, the move happens immediately and automatically.

Simplified version of what's happening inside the STL
<pre>
vector(vector&& other) noexcept {
    this->data_ptr = other.data_ptr;  // I take your address
    this->size     = other.size;      // I take your count
    this->capacity = other.capacity;  // I take your limit

    // THE CLEANUP (Preventing the "Double Free")
    other.data_ptr = nullptr;         // You now point to nothing
    other.size     = 0;
    other.capacity = 0;
}
</pre>

std::move is nothing but a message to the compiler that call the move constructor or move assignment operator for this value. If you look at the source code for std::move, it’s actually surprisingly simple. It doesn't contain any logic to move bits or clear memory. It is essentially just a **type cast**. moving an object that doesn't have a move constructor (or it's deleted), the compiler won't throw an error. It will just say:

"Well, I can't move it, so I'll just fall back to the Copy Constructor instead."




