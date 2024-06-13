#include <memory>
#include <iostream>


// std::forward
struct A {
  A() = default;
  A(const A& o) { std::cout << "copied" << std::endl; }
  A(A&& o) { std::cout << "moved" << std::endl; }
};

template <typename T>
A wrapper(T&& arg) {
  return A{std::forward<T>(arg)};
}

int main() {
    std::unique_ptr<int> ptr(new int(42));
    std::cout << *ptr << std::endl;  // Outputs: 42
    // ptr2 cannot point to the same object as ptr
    // std::unique_ptr<int> ptr2 = ptr;  // Error: unique_ptr is not copyable
    ptr.reset();  // Deletes the owned object
    // *ptr is now invalid


    // It uses reference counting to keep track of how many pointers point to the object.
    // When the last shared_ptr pointing to an object goes out of scope or is reset, 
    // the object is automatically deleted.
    std::shared_ptr<int> ptr1(new int(42));
    std::shared_ptr<int> ptr2 = ptr1;
    std::cout << *ptr1 << std::endl;  // Outputs: 42
    std::cout << *ptr2 << std::endl;  // Outputs: 42
    // Both ptr1 and ptr2 point to the same object
    ptr1.reset();  // Decreases the reference count
    // The object is not deleted because ptr2 still refers to it
    std::cout << *ptr2 << std::endl;  // Outputs: 42
    ptr2.reset();  // Deletes the object
    // *ptr1 and *ptr2 are now invalid

    std::shared_ptr<int> sharedPtr(new int(42));
    std::weak_ptr<int> weakPtr = sharedPtr;
    if (auto lockedPtr = weakPtr.lock()) {
        // Use lockedPtr as long as the object exists
        std::cout << *lockedPtr << std::endl;  // Outputs: 42
    } else {
        std::cout << "Object no longer exists" << std::endl;
    }
    sharedPtr.reset();  // Deletes the object
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << *lockedPtr << std::endl;  // This block won't execute
    } else {
        std::cout << "Object no longer exists" << std::endl;  // Outputs: Object no longer exists
    }

    wrapper(A{}); // moved
    A a;
    wrapper(a); // copied
    wrapper(std::move(a)); // moved
    return 0;
}
