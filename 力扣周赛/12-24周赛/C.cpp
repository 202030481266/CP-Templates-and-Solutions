class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        int n = price.size();
        sort(price.begin(), price.end());

        int l = 0, r = price.back() - price[0];

        auto f = [&](int x) {
            int cnt = 1, last = price[0];
            for (int i = 1; i < n; i++) {
                if (price[i] - last >= x) {
                    ++cnt;
                    last = price[i];
                }
            }
            return cnt >= k;
        };
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (f(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        assert(ans != -1);
        return ans;
    }
};