# Why initialization list is better than assigning inside constructor

<pre>
class UserManager {
  std::string username_; // This is an object, not a raw pointer!

  UserManager(std::string name) {
    username_ = name; 
    // 1. username_ is "Default Constructed" (Internal heap allocation for 
    an empty string).
    // 2. username_ is "Assigned" (Deletes its old memory, allocates 
    NEW heap memory for 'name').
  }
};
</pre>
Hence we throw away(free it ofc) the heap space allocated during the default 
construction of the `std::string username_` object.

# Operator associativity direction

## Right-Left

Assignment is the most famous member, but it's not alone. Here are the others that flow from right-to-left:

- Assignment Operators: =, +=, -=, *=, /=, %=, <<=, >>=, &=, ^=, |=

- Unary Operators (One-handed): ++ (prefix), -- (prefix), + (unary plus), - (unary minus), ! (not), ~ (bitwise NOT), * (dereference), & (address-of), and sizeof.<br><br>
Why Unary Operators are Right-to-Left:<br>
Think about this expression: *&x (the value at the address of x)
    - First, you find the address of x (&x)
    - Then, you dereference that result (*).

- The Ternary Operator: ? : (e.g., a ? b : c ? d : e evaluates as a ? b : (c ? d : e)).

## Left-Right

You are correct that the vast majority of operators used in daily logic are left-associative. This matches how we read Western languages and standard arithmetic:

- Arithmetic: +, -, *, /, %

- Relational/Comparison: <, >, <=, >=, ==, !=

- Logical: &&, ||

- I/O: <<, >>

- Member Access: . and -> (e.g., myObj.member.subMember evaluates the left side first).



