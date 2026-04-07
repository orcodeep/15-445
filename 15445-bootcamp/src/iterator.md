
<pre>
// Implementing a prefix increment operator (++iter).
DLLIterator& operator++() {
  curr_ = curr_->next_;
  return *this;
}
</pre>

**Here we return a reference to a DLLIterator object as this object already exists we just updated its internal `curr_` ptr. No need to make a copy.**

The DllIterator class doesnt need a destructor as it just contains a ptr. The trivial destructor is enough.

<pre>
// Implementing a postfix increment operator (iter++). The difference
// between a prefix and postfix increment operator is the return value
// of the operator. The prefix operator returns the result of the
// increment, while the postfix operator returns the iterator before
// the increment.
// This is made to resemble primitive c++ iterators. int x = 5, y; y = x++; y gets 5 then x becomes 6
DLLIterator operator++(int) {
  DLLIterator temp = *this;
  ++*this;
  return temp;
}
</pre>

**Here we return object type as we want temp to be created on the caller's stack. Or else temp would be destroyed as soon as it goes out of scope of the operator and the object in the caller's scope would touch memory that's not its and will misbehave**


