class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int n = chargeTimes.size();
        int l = 0, ans = 0, st = 0, ed = 0; // [st, ed)
        long long sum = 0;
        vector<int> q(n + 1);
        for (int i = 0; i < n; ++i) {
            sum += runningCosts[i];
            while (st < ed && chargeTimes[q[ed - 1]] < chargeTimes[i]) --ed;
            q[ed++] = i;
            while (l <= i && chargeTimes[q[st]] + (i - l + 1) * sum > budget) {
                sum -= runningCosts[l];
                ++l;
                while (st < ed && q[st] < l) ++st;
            }
            ans = max(ans, i - l + 1);
        }
        return ans;
    }
};