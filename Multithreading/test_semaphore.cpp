// https://leetcode.com/tag/concurrency/
#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t s;

void init () {
	cout << "starting here" << endl;
	sem_post(&s);
}

void printNumbers () {
	int i = 0;
	while (i < 5) {
		sem_wait(&s);
		cout << i << endl;
		i++;
		sem_post(&s);
	}
}

/* LC#1115

The same instance of FooBar will be passed 
to two different threads:

thread A will call foo(), while
thread B will call bar().
Modify the given program to output "foobar" n times
so that foo and bar are printed alternatively.
*/

class FooBar {
private:
    int n;
    sem_t semFoo, semBar;
public:
    FooBar(int n) {
        this->n = n;
        sem_init(&semFoo, 0, 1);
        sem_init(&semBar, 0, 0);
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            sem_wait(&semFoo);
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            sem_post(&semBar);
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            sem_wait(&semBar);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            sem_post(&semFoo);
        }
    }
};


/* LC#1114

The same instance of Foo will be passed to three different threads. 
Thread A will call first(), thread B will call second(), 
and thread C will call third(). 
Design a mechanism and modify the program to ensure 
that second() is executed after first(), 
and third() is executed after second().

Note:

We do not know how the threads will be scheduled 
in the operating system, 
even though the numbers 
in the input seem to imply the ordering. 
The input format you see is mainly to ensure our tests' comprehensiveness.

Constraints:
nums is a permutation of [1, 2, 3].
*/

class Foo {
private:
    sem_t semFirst, semSecond, semThird;
public:
    Foo() {
        sem_init(&semFirst, 0, 1);
        sem_init(&semSecond, 0, 0);
        sem_init(&semThird, 0, 0);
    }

    void first(function<void()> printFirst) {
        sem_wait(&semFirst);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&semSecond);
    }

    void second(function<void()> printSecond) {
        sem_wait(&semSecond);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(&semThird);
    }

    void third(function<void()> printThird) {
        sem_wait(&semThird);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        sem_post(&semFirst);
    }
};


/* LC#1116

You have a function printNumber 
that can be called with an integer parameter 
and prints it to the console.

For example, 
calling printNumber(7) prints 7 to the console.
You are given an instance of the class ZeroEvenOdd 
that has three functions: zero, even, and odd. 
The same instance of ZeroEvenOdd will be passed 
to three different threads:

Thread A: calls zero() that should only output 0's.
Thread B: calls even() that should only output even numbers.
Thread C: calls odd() that should only output odd numbers.
Modify the given class to output the series "010203040506..." 
where the length of the series must be 2n.

Implement the ZeroEvenOdd class:

ZeroEvenOdd(int n) Initializes the object 
with the number n that represents the numbers that should be printed.
void zero(printNumber) Calls printNumber to output one zero.
void even(printNumber) Calls printNumber to output one even number.
void odd(printNumber) Calls printNumber to output one odd number.
*/

class ZeroEvenOdd {
private:
    int n;
    sem_t semZero, semEven, semOdd;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&semZero, 0, 1);
        sem_init(&semEven, 0, 0);
        sem_init(&semOdd, 0, 0);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= this->n; i++) {
            sem_wait(&semZero);
            printNumber(0);
            if (i % 2 == 0)
                sem_post(&semEven);
            else 
                sem_post(&semOdd);
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= this->n; i += 2) {
            sem_wait(&semEven);
            printNumber(i);
            sem_post(&semZero); 
        } 
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= this->n; i += 2) {
            sem_wait(&semOdd);
            printNumber(i);
            sem_post(&semZero);
        }
    }
};

/* LC#1195

You are given an instance of the class FizzBuzz 
that has four functions: fizz, buzz, fizzbuzz and number. 
The same instance of FizzBuzz will be passed to four different threads:

Thread A: calls fizz() that should output the word "fizz".
Thread B: calls buzz() that should output the word "buzz".
Thread C: calls fizzbuzz() that should output the word "fizzbuzz".
Thread D: calls number() that should only output the integers.
Modify the given class to output the series [1, 2, "fizz", 4, "buzz", ...] 
where the ith token (1-indexed) of the series is:

"fizzbuzz" if i is divisible by 3 and 5,
"fizz" if i is divisible by 3 and not 5,
"buzz" if i is divisible by 5 and not 3, or
i if i is not divisible by 3 or 5.
*/

class FizzBuzz {
private:
    int n, curr;
    sem_t semFizz, semBuzz, semFizzBuzz, semNum;
public:
    FizzBuzz(int n) {
        this->n = n;
        this->curr = 1;
        sem_init(&semNum, 0, 1);
        sem_init(&semBuzz, 0, 0);
        sem_init(&semFizz, 0, 0);
        sem_init(&semFizzBuzz, 0, 0);
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        // while (this->curr <= this-> n) {
        for (int i = 3; i <= n && i % 5 != 0; i += 3) {
            sem_wait(&semFizz);
            printFizz();
            // this->curr++;
            sem_post(&semNum);
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        // while (this->curr <= this-> n) {
        for (int i = 5; i <= n && i % 3 != 0; i += 5) {
            sem_wait(&semBuzz);
            printBuzz();
            // this->curr++;
            sem_post(&semNum);
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        //while (this->curr <= this-> n) {
        for (int i = 15; i <= this->n; i+= 15) {
            sem_wait(&semFizzBuzz);
            printFizzBuzz();
            sem_post(&semNum);
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (this->curr <= this-> n) {
            sem_wait (&semNum);
            // int i = this->curr; this->curr++;
            if (this->curr % 3 == 0 && this->curr % 5 == 0) {
                this->curr++;
                sem_post(&semFizzBuzz);
            }
            else if (this->curr % 3 == 0 && this->curr % 5 != 0) {
                this->curr++;
                sem_post(&semFizz);
            }
            else if (this->curr % 3 != 0 && this->curr % 5 == 0) {
                this->curr++;
                sem_post(&semBuzz);
            }
            else {
                printNumber(this->curr);
                this->curr++;
                sem_post(&semNum);
            }
            
        }
    }
};

int main () {
	sem_init(&s, 0, 0);
	std::thread th1(init);
	std::thread th2(printNumbers);
	th1.join(); th2.join();
	sem_destroy(&s);

	FooBar fb(4);

	return 0;
}