class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        int n = ranks.size();

        auto f = [&](long long time) {
            long long cnt = 0;
            for (int i = 0; i < n; ++i) {
                cnt += (long long)sqrt(time / ranks[i]);
            }
            return cnt >= cars;
        };

        long long l = 1, r = 10e17 + 1;
        long long ans = -1;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (f(mid))
                ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        assert(ans != -1);
        return ans;
    }
};