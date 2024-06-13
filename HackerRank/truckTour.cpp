/*

Truck Tour

There is a circle with N oil pumps, ranging 0 ... N -1.
The truck has infinite tank capacity 
but zero fuel in the beginning.

From which index it can start (0, 1, 2, or so),
where it can complete the cycle amnd come back to that point.
For each indexed oil pump, 
given <amount of fuel (in gallon) the truck can get, 
the distance to the next pump (in mile)>.

With each gallon fuel, the truck can run a mile.
*/


int truckTour(vector<vector<int>> petrolpumps) {
    int n = petrolpumps.size();
    vector<vector<int>> petrolpumps_cpy = petrolpumps;
    petrolpumps.insert(petrolpumps.end(), petrolpumps_cpy.begin(), petrolpumps_cpy.end());
    for (int i = 0; i < n; i++) {
        int petrol = petrolpumps[i][0];
        int j = i;
        while (j < i + n) {
            petrol -= petrolpumps[j][1];
            if (petrol < 0)
                break;
            j++;
            petrol += petrolpumps[j][0];
        }
        if (j == i + n)
            return i;
    }
    return -1;
}