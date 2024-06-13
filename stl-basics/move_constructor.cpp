#include <iostream>

class MyResource {
private:
    int* data;  // Pointer to dynamically allocated memory

public:
    // Default constructor
    MyResource() : data(nullptr) {}

    // Constructor with dynamic memory allocation
    MyResource(int size) : data(new int[size]) {
        std::cout << "Constructor: Allocated memory" << std::endl;
    }

    // Move constructor (&& indicates an rvalue reference)
    MyResource(MyResource&& other) noexcept : data(other.data) {
        std::cout << "Move Constructor: Moved resources" << std::endl;
        other.data = nullptr;  // Reset the other object's pointer
    }
    // noexcept indicates that the move constructor does not throw any exceptions. 
    // This is important for move operations because they are expected to be efficient 
    // and not involve any operations that might throw exceptions.

    void printData() {
        if (data) {
            std::cout << *this->data << std::endl;
        }
        else {
            std::cout << "No data" << std::endl;
        }
    }

    // Destructor to release allocated memory
    ~MyResource() {
        if (data) {
            delete[] data;
            std::cout << "Destructor: Deallocated memory" << std::endl;
        }
    }
};

int main() {
    // Create a temporary object (rvalue)
    MyResource temp(5);
    temp.printData();

    // Move construct a new object using the temporary object
    MyResource obj(std::move(temp));

    temp.printData();
    obj.printData();

    return 0;
}
