#include <iostream>

class MyString {
private:
    char* buffer;
    size_t length;

public:
    // Constructor
    MyString(const char* str) {
        length = strlen(str);
        buffer = new char[length + 1];
        strcpy(buffer, str);
    }

    // Destructor
    ~MyString() {
        delete[] buffer;
    }

    // Copy assignment operator
    MyString& operator=(const MyString& other) {
        if (this != &other) { // Check for self-assignment
            delete[] buffer; // Free existing buffer
            length = other.length; // Copy length
            buffer = new char[length + 1]; // Allocate new buffer
            strcpy(buffer, other.buffer); // Copy data
        }
        return *this; // Return reference to the updated object
    }

    // Getter for buffer
    const char* getBuffer() const {
        return buffer;
    }
};

int main() {
    MyString str1("Hello");
    MyString str2("World");

    std::cout << "str1: " << str1.getBuffer() << std::endl; // Outputs: World
    std::cout << "str2: " << str2.getBuffer() << std::endl; // Outputs: World

    // Copy assignment
    str1 = str2;

    std::cout << "str1: " << str1.getBuffer() << std::endl; // Outputs: World
    std::cout << "str2: " << str2.getBuffer() << std::endl; // Outputs: World

    return 0;
}
