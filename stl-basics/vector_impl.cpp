#include <iostream>
#include <algorithm>  // For std::copy
#include <stdexcept>  // For std::out_of_range

template<typename T>
class MyVector {
public:
    // Constructor
    MyVector() : capacity_(0), size_(0), data_(nullptr) {}
    
    // Destructor
    ~MyVector() { delete[] data_; }

    // Copy constructor
    MyVector(const MyVector& other) : capacity_(other.capacity_), size_(other.size_) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Copy assignment
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Move constructor
    MyVector(MyVector&& other) noexcept : capacity_(0), size_(0), data_(nullptr) {
        swap(other);
    }

    // Move assignment
    MyVector& operator=(MyVector&& other) noexcept {
        swap(other);
        return *this;
    }

    // Capacity
    size_t capacity() const { return capacity_; }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Element access
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // dynamic resizing
    // Amortized Constant Time, Worst-Case Linear Time, Doubling Strategy
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    // Other member functions (e.g., reserve, insert, erase, clear, iterators) would go here...

private:
    size_t capacity_;
    size_t size_;
    T* data_;

    void reserve(size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        T* newData = new T[newCapacity];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void swap(MyVector& other) noexcept {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }
};

int main() {
    MyVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
