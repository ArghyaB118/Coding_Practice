/* LC#1188

Implement a thread-safe bounded blocking queue that has the following methods:

BoundedBlockingQueue(int capacity) 
The constructor initializes the queue with a maximum capacity.
void enqueue(int element) Adds an element to the front of the queue. 
If the queue is full, the calling thread is blocked until the queue is 
no longer full.
int dequeue() Returns the element at the rear of the queue and removes it. 
If the queue is empty, the calling thread is blocked until the queue is 
no longer empty.
int size() Returns the number of elements currently in the queue.

Your implementation will be tested using multiple threads at the same time. 
Each thread will either be a producer thread that only makes calls 
to the enqueue method or a consumer thread that only makes calls 
to the dequeue method. 
The size method will be called after every test case.

Please do not use built-in implementations of bounded blocking queue as this will not be accepted in an interview.
*/
#include <iostream>
#include <queue>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
// #include <semaphore.h>
using namespace std;

vector<int> arr = {1, 2, 3, 4, 5, 6};

// beats ~70% LC users
class BoundedBlockingQueue {
private:
    queue<int> q;
    mutex mtx;
    condition_variable unfull, unempty;
    int n, count;
public:
    BoundedBlockingQueue(int capacity) {
        this->n = capacity;
        this->count = 0;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lock(mtx);
        unfull.wait(lock, [this] { return this->count < this->n; });
        q.push(element);
        this->count++;
        unempty.notify_one();
    }
    
    int dequeue() {
        unique_lock<mutex> lock(mtx);
        unempty.wait(lock, [this] { return this->count > 0; });
        int v = q.front();
        q.pop();
        this->count--;
        unfull.notify_one();
        return v;
    }
    
    int size() {
        lock_guard<mutex> lock(mtx);
        return this->count;
    }
};

void thread_enqueue (BoundedBlockingQueue b) {
    for (int i = 0; i < arr.size(); i++)
        b.enqueue(arr[i]);
}

void thread_dequeue (BoundedBlockingQueue b) {
    for (int i = 0; i < arr.size(); i++)
        b.dequeue();
}

// beats ~25% LC users
class BoundedBlockingQueue2 {
private:
    queue<int> q;
    sem_t unempty, unfull;
public:
    BoundedBlockingQueue2(int capacity) {
        sem_init(&unfull, 0, capacity);
        sem_init(&unempty, 0, 0);
    }

    ~BoundedBlockingQueue2() {
        sem_destroy(&unempty);
        sem_destroy(&unfull);
    }

    void enqueue (int element) {
        sem_wait(&unfull);
        q.push(element); 
        sem_post(&unempty);
    }

    int dequeue () {
        sem_wait(&unempty);
        const int v =  q.front(); // this const is needed
        q.pop(); 
        sem_post(&unfull);
        return v;
    }
    
    int size() {
        return q.size();
    }
};

int main () {
    BoundedBlockingQueue b(3);
    std::thread thread1(thread_enqueue, b);
    std::thread thread2(thread_dequeue, b);
    thread1.join(); thread2.join();
    return 0;
}