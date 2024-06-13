#include <iostream>
// #include <boost/random.hpp>

#include <cstdlib>
#include <ctime>

#include <random>

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate and print random numbers
    for (int i = 0; i < 5; ++i) {
        std::cout << std::rand() % 10 + 1 << " ";
    }
    std::cout << std::endl;

/* not working on mac, even after installing and including path to boost
by using `brew install boost` and `brew --prefix boost`
then `g++ -I /opt/homebrew/opt/boost -std=c++11 random.cpp`
    // Create a random number generator
    boost::random::mt19937 rng;

    // Create a uniform distribution for integers in a range
    boost::random::uniform_int_distribution<> dist(1, 10);

    // Generate and print random numbers
    for (int i = 0; i < 5; ++i) {
        std::cout << dist(rng) << " ";
    }
    std::cout << std::endl;
*/
    // Create a random number engine with a seed from the operating system's random number generator.
    std::random_device rd;
    // A pseudo-random number generator (PRNG) known as the Mersenne Twister engine
    // Advantage of Mersenne Twister: High periodicity (2^19937 −1) but fast, high randomness.
    std::mt19937 rng(rd());

    // Create a uniform distribution for integers in a range
    std::uniform_int_distribution<int> dist(1, 10);
    // std::normal_distribution<double> dist(5.0, 2.0); // for normal distro


    // Generate and print random numbers
    for (int i = 0; i < 5; ++i) {
        std::cout << dist(rng) << " ";
    }
    std::cout << std::endl;

    return 0;
}
