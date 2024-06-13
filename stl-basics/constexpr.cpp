#include <iostream>
using namespace std;

constexpr int square(int x) { return x * x; }

int square2(int x) { return x * x; }

const int x = 123;
constexpr const int& y = x; // error -- constexpr variable `y` must be initialized by a constant expression  

// works only on cpp14
constexpr int factorial(int n) {
  if (n <= 1) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int main () {
  int a = square(2);
  int b = square2(2);
  cout << a << " " << b << " " << y << endl;
  cout << factorial(5) << endl;
  return 0;
}
