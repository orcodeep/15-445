# std::remove_if

1. `std::vector::erase` is inefficient enough to be ignored.
- If you have 1,000 items and you erase the first one, every single one of the remaining 999 items has to be physically shifted one spot to the left to fill the gap. 

2. Instead of shifting all elements after hitting target, `std::remove_if` does a single pass and pushes the target elements to the end and shifts all the rest 
once and passes a iterator object to `std::vector::erase` as its first arg.


