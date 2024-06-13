#include <iostream>
#include <string>
#include <functional>

struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    ~Point() {}
};

// Custom hash function for Point struct
struct PointHash {
    size_t operator()(const Point& p) const {
        size_t hashX = std::hash<int>{}(p.x);
        size_t hashY = std::hash<int>{}(p.y);
        return hashX ^ (hashY << 1); // Combining hash values
    }
};

int main() {
    std::hash<std::string> hasher;
    std::string key = "Hello, World!";
    size_t hashValue = hasher(key);
    std::cout << "Key: " << key << std::endl;
    std::cout << "Hash value: " << hashValue << std::endl;

    Point p = {10, 20};
    PointHash pHasher;
    size_t pHashValue = pHasher(p);
    std::cout << "Hash value: " << pHashValue << std::endl;
    
    return 0;
}
