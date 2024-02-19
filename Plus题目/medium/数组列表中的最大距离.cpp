class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        // 需要注意的是最大最小值可能出现同一个数组中
        int mn1 = INT_MAX, mn2 = INT_MAX;
        int mx1 = INT_MIN, mx2 = INT_MIN;
        int id1 = -1, id2 = -1, id = 0;
        for (vector<int>& a : arrays) {
            int x = a[0], y = a.back();
            if (x < mn1) {
                mn2 = mn1;
                mn1 = x;
                id1 = id;
            }
            else if (x < mn2) mn2 = x;
            if (y > mx1) {
                mx2 = mx1;
                mx1 = y;
                id2 = id;
            }
            else if (y > mx2) mx2 = y;
            ++id;
        }
        if (id1 != id2) return mx1 - mn1;
        else return max({mx1 - mn2, mx2 - mn1});
    }
};