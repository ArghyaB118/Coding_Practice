#include <iostream>
#include <chrono>
#include <ctime>


int main() {
    // Why is it better than ctime?
    // 1. type-safety, units and conversions are easier
    // 2. more precision: std::chrono::system_clock, std::chrono::steady_clock, and std::chrono::high_resolution_clock.
    // 3. supports template, type deduction, constexpr
    // Get the current time point using system clock
    auto start = std::chrono::system_clock::now();

    // Perform some time-consuming operation (simulated delay)
    for (int i = 0; i < 1000000000; ++i) {
        // Do some computation (dummy loop)
        int x = i * i;
    }

    // Get the current time point again
    auto end = std::chrono::system_clock::now();

    // Calculate the elapsed time duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the elapsed time in milliseconds
    std::cout << "Elapsed time: " << duration.count() << " milliseconds" << std::endl;


    // The time() function returns the current system time 
    // as the number of seconds since the epoch 
    // (00:00:00 Coordinated Universal Time (UTC), January 1, 1970). 
    // This value is of type time_t.
    
    // Function Signature: time_t time(time_t* timer);
    // timer is a pointer to a time_t object 
    // where the result will be stored. 
    // If timer is not nullptr, the result is also stored in the pointed object.
    time_t startTime = time(nullptr);
    // Perform some time-consuming operation (simulated delay)
    for (int i = 0; i < 1000000000; ++i) {
        // Do some computation (dummy loop)
        int x = i * i;
    }
    time_t endTime = time(nullptr);
    // Print the elapsed time in seconds
    std::cout << "Elapsed time: " << endTime - startTime << " seconds" << std::endl;


    return 0;
}
