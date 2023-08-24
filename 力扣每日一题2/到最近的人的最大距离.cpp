class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();
        vector<int> one;
        for (int i = 0; i < n; ++i)
            if (seats[i]) one.push_back(i);
        int ans = 0;
        for (int i = 0; i < one.size() - 1; ++i) {
            int mid = (one[i] + one[i + 1]) / 2;
            if (mid > one[i]) {
                ans = max(ans, mid - one[i]);
            }
        }
        if (one[0] != 0) ans = max(ans, one[0]);
        if (one.back() != n - 1) ans = max(ans, n - 1 - one.back());
        return ans;
    }
};