/* LC#1279

There is an intersection of two roads. 
First road is road A where cars travel 
from North to South in direction 1 
and from South to North in direction 2. 
Second road is road B where cars travel 
from West to East in direction 3 
and from East to West in direction 4.

There is a traffic light located 
on each road before the intersection. 
A traffic light can either be green or red.

Green means cars can cross the intersection 
in both directions of the road.
Red means cars in both directions 
cannot cross the intersection 
and must wait until the light turns green.
The traffic lights cannot be green 
on both roads at the same time. 
That means when the light is green on road A, 
it is red on road B 
and when the light is green on road B, 
it is red on road A.

Initially, the traffic light is green on road A 
and red on road B. 
When the light is green on one road, 
all cars can cross the intersection 
in both directions until the light becomes green 
on the other road. 
No two cars traveling on different roads 
should cross at the same time.

Design a deadlock-free traffic light 
controlled system at this intersection.

Implement the function 
void carArrived(carId, roadId, direction, turnGreen, crossCar) where:

carId is the id of the car that arrived.
roadId is the id of the road that the car travels on.
direction is the direction of the car.

turnGreen is a function you can call 
to turn the traffic light to green on the current road.

crossCar is a function you can call 
to let the current car cross the intersection.

Your answer is considered correct 
if it avoids cars deadlock in the intersection. 
Turning the light green on a road 
when it was already green is considered a wrong answer.
*/

class TrafficLight {
private:
    int greenRoad = 1;
    mutex mtx;
public:
    TrafficLight() {}

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        {
            lock_guard<mutex> lock(mtx);
            if (roadId != this->greenRoad) {
                turnGreen();
                this->greenRoad = roadId;
            }
        }
        crossCar();
    }
};