/**
 * @file unique_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a unique pointer.
 */

// A smart pointer is a type of data structure used for memory management (and
// sometimes other features) in languages that don't have memory management
// built in (e.g C++) An example of a language that has memory management built
// in is any language with garbage collection, like Java or Python. Two of the
// modern C++ standard library's smart pointers (and the ones that you will use
// in class) are std::unique_ptr and std::shared_ptr. Both std::unique_ptr and
// std::shared_ptr handle memory allocation and deallocation automatically, and
// contain raw pointers under the hood. In other words, they are wrapper classes
// over raw pointers. In this file, we'll talk about std::unique_ptr.
// std::unique_ptr is a type of smart pointer that retains sole ownership of an
// object This means that no two instances of std::unique_ptr can manage the
// same object.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes std::unique_ptr functionality.
#include <memory>
// String library for printing help for demo purposes.
#include <string>
// Including the utility header for std::move.
#include <utility>

// Basic point class. (Will use later)
class Point {
public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  inline int GetX() { return x_; }
  inline int GetY() { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }

private:
  int x_;
  int y_;
};

// Function that takes in a unique pointer reference and changes its x value to 445.
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); } //**remember here no constructor is being called
// you can have a pass by value unique_ptr argument in a function. But, u gotta use std::move() while passing it to the function.
// It wont compile otherwise. The moment the compiler sees someFunction(my_Uptr), it says: "Okay, the function wants p by value. 
// That means I need to duplicate my_ptr into p using the Copy Constructor." Then it checks the std::unique_ptr class definition, 
// sees unique_ptr(const unique_ptr&) = delete;, and completely halts compilation. 'cause The heavy underlying object sitting 
// on the heap is never duplicated. You are just copying the address of that underlying object which means there would be
// multiple references to the same object. which a unique_ptr doesnt permit. (a shared_ptr does)

/* Hence you only have the move constructor that works:-

void rprocess(std::unique_ptr<Point>&& p_local) {
    // p_local is just a reference. It does NOT own it yet.
    std::cout << p_local->x; 
} // Nothing is deleted here!

void process(std::unique_ptr<Point> p_local) {
    // p_local owns it now
} // The Point is DELETED here!

Pass by Value (std::unique_ptr<Point> ptr): The function demands a brand-new box on its own stack frame. To build that box, 
it must use a constructor (either copy or move). If you try to pass an lvalue, it tries to use the deleted copy constructor and 
fails. **Also check unique_ptr.md for why pass-by-value cannot use the Normal constructor instead if u forgot.

int main() {
    auto my_ptr = std::make_unique<Point>(1, 2);
    process(std::move(my_ptr)); // rprocess() chose not to steal it, so my_ptr is still valid!
    process(std::move(my_ptr)); // my_ptr will be emptied before process even starts.
}
*/

/*
C++ lets you create a pointer to a reference, which is written syntax-wise as T*&
It is easiest to think of it this way: a reference to a pointer is just an alias (another name) for an existing pointer variable.

Why would you ever need this? (speaking in terms of a raw ptr):-

The most common reason to use a reference to a pointer is when you want a function to modify a pointer that was passed into it (like 
changing its memory address or allocating new memory for it).
The Problem: Passing a Pointer by Value

If you pass a regular pointer into a function, the function gets a copy of that pointer. If you change where the pointer points 
inside the function, the original pointer outside the function doesn't change!

To achieve the exact same result in C—where a function modifies a pointer from the outside world—you had to pass a pointer to a 
pointer
*/

int main() {
  // This is how to initialize an empty unique pointer of type std::unique_ptr<Point>.
  std::unique_ptr<Point> u1; /* Under the hood: It is initialized to nullptr. It doesn't point to any object on the heap yet, and no 
                                memory has been allocated for a Point. It’s just an empty RAII shell waiting for an assignment. */

  // This is how to initialize a unique pointer with the default constructor.
  std::unique_ptr<Point> u2 = std::make_unique<Point>();
  // This is how to initialize a unique pointer with a custom constructor.
  std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);
  /* std::make_unique (The helper function template): It goes out to the heap, calls new, allocates the raw memory, 
   * and constructs your object inside that memory. 
   * std::unique_ptr immediately takes ownership of that raw pointer from std::make_unique. 
   * It wraps it safely inside its RAII shell and guarantees that delete will be called when it goes out of scope.*/

  // Here, for std::unique_ptr instance u, we use the statement (u ? "not empty"
  // : "empty") to determine if the pointer u contains managed data. The main
  // gist of this is that the std::unique_ptr class has a conversion function on
  // its objects to a boolean type, and so this function is called whenever we
  // treat the std::unique_ptr as a boolean. For instance, this can be used in
  // the following example.
  if (u1) {
    // This won't print because u1 is empty.
    std::cout << "u1's value of x is " << u1->GetX() << std::endl;
  }

  if (u2) {
    // This will print because u2 is not empty, and contains a managed Point
    // instance.
    std::cout << "u2's value of x is " << u2->GetX() << std::endl;
  }

  // Note that u1 is empty and u2 and u3 are not empty, since they were
  // initialized with a Point instance.
  std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

  // Since instances of std::unique_ptr can have only one owner, it has no copy
  // constructor. Therefore, this code won't compile. Uncomment it to try!
  // std::unique_ptr<Point> u4 = u3;

  // However, it's possible to transfer ownership of unique pointers via
  // std::move.
  std::unique_ptr<Point> u4 = std::move(u3); // here we are actually calling the move constructor of unique_ptr class template 
                                             // not the move assignment operator

  // Note that because u3 is an lvalue, it no longer contains any managed
  // object. It is an empty unique pointer. 

  /* If a unique pointer u4 already existed before and was not created on spot and was already pointing to a valid object 
     on the heap, doing a move-assignment like u4 = std::move(u3); triggers a double action: it safely destroys its own 
     old object first, and then steals the new one. */

  // Let's retest for emptyness.
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;

  // Lastly, let's talk about how to pass std::unique_ptr instances as arguments
  // to functions. Mainly, you should pass it as a reference so that the
  // ownership doesn't change. You can see this as an example in the function
  // SetXTo445 (line 44 in this file).
  SetXTo445(u4);

  // Now, let's print the x value of u4 to confirm that the change occured, but
  // the ownership of the Point instance has been retained to u4.
  std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

  return 0;
}
