In
```cpp
Person(uint32_t age, std::vector<std::string> &&nicknames)
    : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}
```
`nickname_` is ofcourse a vector type so using std::move will ensure the move constructor is
called and nicknames(which is a lvalue now after entering the function) is not copied.

In
```cpp
Person &operator=(Person &&other) {
std::cout << "Calling the move assignment operator for class Person.\n";
age_ = other.age_;
nicknames_ = std::move(other.nicknames_);
valid_ = true;

// The moved object's validity tag is set to false.
other.valid_ = false;
return *this;
}
```
Even though we are returning a Person lvalue ref type(for chaining) the move constructor wont
be called after the rightmost `=` in the chain(say p1 = p2 **`=`** std::move(p3)). 
- This is why move assignment is never chained in practice.

That's cause `p1.operator=` expects a rvalue ref but `p2.operator=` returns a lvalue ref.

- Its a design principle that Assignment should look like Assignment, regardless of whether it's a copy or a move.

    - If operator=(const T&) returns T&.

    - Then operator=(T&&) should also return T&.

    This allows template code (code written to work with any type) to treat your object predictably. If a template expects to be able to use the result of an assignment, and your move assignment returns void, that template will break specifically when a move happens.

- By returning *this, you allow the chain to continue, even if it has to downshift from a "move" to a "copy." which is better than a compilation error in chain.

- **The "Self-Documentation" of Types**

    Returning Person& tells the compiler and other developers: "This object is still alive and ready for more instructions." Even if you don't use it for chaining, it maintains the identity of the object.




