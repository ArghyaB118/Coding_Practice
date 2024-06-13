#include <cstdlib>
#include <iostream> // only for cout

#include <sys/mman.h>
using namespace std;

int main () {
    // how would you do it in C? answer: malloc
    int* ptr = static_cast<int*>(std::malloc(sizeof(int)));
    if (ptr != nullptr) {
        *ptr = 42;
        std::cout << ptr << " " << *ptr << " " << &ptr << std::endl;
        std::free(ptr); // Manual deallocation
    }


    int num_elements = 5;
    int* array = (int*)calloc(num_elements, sizeof(int));
    if (array != NULL) {
        for (int i = 0; i < num_elements; i++) {
            printf("%d ", array[i]); // Will print 0 0 0 0 0
        }
        free(array); // Don't forget to free the allocated memory
        std::cout << std::endl;
    } else {
        printf("Memory allocation failed.\n");
    }

    // placement of new in pre-allocated memory
    void* buff = malloc(sizeof(int));
    int* ptr1 = new (buff) int(4);
    cout << ptr1 << " " << *ptr1 << " " << &ptr1 << endl;

    const size_t size = num_elements * sizeof(int);
    void* arr_space = mmap(NULL, size, 
        PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 
        -1, 0);
    if (arr_space == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    int* arr = static_cast<int*>(arr_space);
    const int values[5] = {1, 2, 3, 4, 5};
    std::memcpy(arr, values, size);

    for (int i = 0; i < num_elements; i++)
        cout << arr[i] << " ";
    cout << endl;

    if (munmap(arr_space, size) == -1) {
        std::cerr << "Error unmapping memory: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    // file backed mmap
    int fd = open("input.txt", O_RDONLY); // Open the file for reading
    if (fd == -1) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Determine the size of the file
    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET); // Rewind to the beginning of the file

    const size_t size = file_size; // Size of the mapped memory is the same as the file size
    void* addr = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0); // Map the file into memory
    if (addr == MAP_FAILED) {
        std::cerr << "Error mapping memory: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    int* data = static_cast<int*>(addr); // Treat the mapped memory as an integer array

    // Read and print the integers from the mapped memory
    size_t num_integers = size / sizeof(int);
    for (size_t i = 0; i < num_integers; ++i) {
        std::cout << "Integer[" << i << "]: " << data[i] << std::endl;
    }

    if (munmap(addr, size) == -1) {
        std::cerr << "Error unmapping memory: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    close(fd); // Close the file descriptor
    return 0;
}
