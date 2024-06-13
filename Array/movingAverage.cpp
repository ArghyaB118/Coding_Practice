/* LC#346

Given a stream of integers and a window size, 
calculate the moving average 
of all integers in the sliding window.

Implement the MovingAverage class:

MovingAverage(int size) Initializes the object 
with the size of the window size.
double next(int val) Returns the moving average 
of the last size values of the stream.
*/

class MovingAverage {
int size, sum;
queue<int> q;
public:
    MovingAverage(int size) {
        this->size = size;
        this->sum = 0;
    }
    
    double next(int val) {
        if (this->q.size() < this->size) {
            this->q.push(val);
            this->sum += val;  
        }
        else {
            this->sum -= this->q.front();
            this->q.pop();
            this->q.push(val);
            this->sum += val;
        }
        return (double)this->sum / this->q.size();
    }
};