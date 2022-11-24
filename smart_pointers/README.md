Implementation of two class templates for smart pointers to `T`: `unique_ptr<T, Deleter>` and `shared_ptr<T>`,
which are simplifications of the corresponding patterns from `std::`.

### Supported operations
Both smart pointers have:

* Default constructor.
* Constructor from `nullptr`.
* Constructor from the pointer to be taken over.
* Move assignment operator.
* Move constructor.
* The `get()` method to get the current value of the pointer.
* The `reset()` method, which resets the current pointer.
* The `reset(x)` method, which transfers ownership of the normal pointer `x` to the smart pointer.
* Overloaded `->` and `*` operators.
* Free function `swap()`.
* Cast operator to `bool`.
* Operators `==` and `!=` to compare smart pointers of the same type.
  Pointers are equal if and only if both point to the same object, or both are `nullptr`.

`unique_ptr` also has:

* A constructor from the pointer to be taken over and the deleting functor.
* The `release()` method that "detaches" the pointer from the smart pointer and returns it.
* Removed copy constructor and copy assignment operator.

`shared_ptr` also has:

* Copy assignment operator.
* Copy constructor.
