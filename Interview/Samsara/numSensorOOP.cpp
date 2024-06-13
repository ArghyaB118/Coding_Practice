#include <iostream>
#include <vector>
#include <string>
using namespace std;


class delivery {
private:
	string destination;
	int distance;
public:
	delivery(string destination_, int distance_) {
		this->destination = destination_;
		this->distance = distance_;
		if (this->distance < 0)
			this->distance = 0;
	}
	int getDistance () {
		return this->distance;
	}
	string getDestination () {
		return this->destination;
	}
	vector<int> getSensors() {
		if (this->distance < 10) 
			return {1, 1, 0};
		else if (this->distance >= 10 && this->distance < 100)
			return {1, 2, 1};
		return {2, 4, 2};
	}
};

class scheduler {
private:
	int gps_n, temp_n, weight_n;
public:
	scheduler (int gps_n_, int temp_n_, int weight_n_) {
		this->gps_n = gps_n_;
		this->temp_n = temp_n_;
		this->weight_n = weight_n_;
	}
	vector<delivery*> getSchedule (vector<delivery*> deliveries) {
		int gps_n_ = 0, temp_n_ = 0, weight_n_ = 0;
		vector<delivery*> result;
		for (auto &d : deliveries) {
			vector<int> num_sensors = d->getSensors();
			if (gps_n_ + num_sensors[0] <= this->gps_n &&
				temp_n_ + num_sensors[1] <= this->temp_n &&
				weight_n_ + num_sensors[2] <= this->weight_n) {
				result.push_back(d);
				gps_n_ += num_sensors[0];
				temp_n_ += num_sensors[1];
				weight_n_ += num_sensors[2];
			}
		}
		return result;
	}
};

int main () {
	delivery* deliveryA = new delivery("A", 9);
	delivery* deliveryB = new delivery("B", 15);
	delivery* deliveryC = new delivery("C", 100);

	scheduler* sch = new scheduler(2, 4, 2);
	vector<delivery*> deliveries({deliveryA, deliveryB, deliveryC});
	vector<delivery*> result = sch->getSchedule(deliveries);
	for (auto &r : result) {
		cout << r->getDestination() << endl;
	}
	return 0;
}