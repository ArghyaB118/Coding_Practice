/* LC#1570

Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) 
Initializes the object with the vector nums

dotProduct(vec) 
Compute the dot product between 
the instance of SparseVector and vec

A sparse vector is a vector that has mostly zero values, 
you should store the sparse vector efficiently 
and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class SparseVector {
	int size;
	unordered_map<int, int> hashmap;
public:
	SparseVector (vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != 0)
				hashmap[i] = nums[i];
		}
		this->size = hashmap.size();
	}

	int dotProduct (SparseVector& vec) {
		int product = 0;
		if (this->size > vec.size) {
			unordered_map<int, int>::iterator it = vec.hashmap.begin();
			while (it != vec.hashmap.end()) {
				if (this->hashmap.find(it->first) != this->hashmap.end())
					product += it->second * this->hashmap[it->first];
				it++;
			}
			return product;
		}
		else {		
			unordered_map<int, int>::iterator it = this->hashmap.begin();
			while (it != this->hashmap.end()) {
				if (vec.hashmap.find(it->first) != vec.hashmap.end())
					product += it->second * vec.hashmap[it->first];
				it++;
			}
		}
		return product;
	}
};

int main () {
	vector<int> nums1{0,1,0,0,2,0,0}, nums2{1,0,0,0,3,0,4};
	SparseVector v1(nums1), v2(nums2);
	cout << "The dot product is: " << v1.dotProduct(v2) << endl;
	return 0;
}