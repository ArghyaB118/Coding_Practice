/* LC#3009

There is a line chart consisting 
of n points connected by line segments. 
You are given a 1-indexed integer array y. 
The kth point has coordinates (k, y[k]). 
There are no horizontal lines; that is, 
no two consecutive points have the same y-coordinate.

We can draw an infinitely long horizontal line. 
Return the maximum number of points 
of intersection of the line with the chart.
*/

int maxIntersectionCount(vector<int>& y) {
    int max_count = 0;
    set<int> yy;
    for (int i = 0; i < y.size(); i++)
        yy.insert(y[i]);

    for (auto i : yy)
        cout << i << endl;
    
    vector<double> yyy;
    int i = *yy.begin();
    for (auto it = yy.begin()++; it != yy.end(); it++) {
        yyy.push_back((double)(i + *it) / 2);
        i = *it;
    }

    for (auto i : yyy)
        cout << i << endl;

    for (int j = 0; j < yyy.size(); j++) {
        int count = 0;
        for (int i = 1; i < y.size(); i++) {
            if (y[i - 1] > yyy[j] && y[i] <= yyy[j])
                count++;
            else if (y[i - 1] < yyy[j] && y[i] >= yyy[j])
                count++;
        }
        max_count = max(max_count, count);
    }
    return max_count;
}