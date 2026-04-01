# Rsn for Self assignment guard need

In a Copy Assignment, self-assignment usually just wastes CPU time. But in a Move
Assignment it can be a "suicide mission" if you don't check for it. 

`a = std::move(a);` without self assignment guard:-
<pre>
IntPtrManager &operator=(IntPtrManager &&other) {
    if (ptr_) {
      delete ptr_; // delete my own memory thinking I am some other object
                      that already existed and have data.
    }
    ptr_ = other.ptr_; // copy the address
    other.ptr_ = nullptr; // you just set your OWN pointer to nullptr.
    return *this; // You are now holding a null pointer
}                    and your data is also deleted.
</pre>





