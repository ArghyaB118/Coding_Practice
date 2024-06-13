/* LC#2956

You are given two 0-indexed integer arrays nums1 and nums2 of sizes n and m, respectively.

Consider calculating the following values:

The number of indices i such that 0 <= i < n and nums1[i] occurs at least once in nums2.
The number of indices i such that 0 <= i < m and nums2[i] occurs at least once in nums1.
Return an integer array answer of size 2 containing the two values in the above order.
*/

// beats ~81% LC users
vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> nums1_elts, nums2_elts;
    for (int &i : nums1)
        nums1_elts.insert(i);
    for (int &i : nums2)
        nums2_elts.insert(i);
    vector<int> count = {0, 0};
    for (int &i : nums1) {
        if (nums2_elts.find(i) != nums2_elts.end())
            count[0]++;
    }
    for (int &i : nums2) {
        if (nums1_elts.find(i) != nums1_elts.end())
            count[1]++;
    }
    return count;
}