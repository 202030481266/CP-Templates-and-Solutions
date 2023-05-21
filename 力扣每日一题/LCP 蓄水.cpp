class Solution {
    typedef pair<int, int> pii;
public:
    int storeWater(vector<int>& bucket, vector<int>& vat) {
        // 最好的决策是先增加水桶容量然后在去装水肯定是最不亏的
        int n = bucket.size();
        auto cal = [&](int a, int b) -> int {
            int x = a / b, y = a % b;
            return (y > 0 ? x + 1 : x);
        };
        // 枚举最后的需要倒水的轮数
        int ans = INT_MAX, mx = 0, at_least = 0;
        for (int i = 0; i < n; ++i) {
            if (bucket[i] == 0) {
                if (vat[i] == 0) continue;
                ++bucket[i], ++at_least;
            }
            mx = max(mx, cal(vat[i], bucket[i]));
        }
        ans = mx;
        for (int j = 1; j <= mx; ++j) {
            int tmp = 0;
            for (int i = 0; i < n; ++i) {
                int x = cal(vat[i], j);
                tmp += (x > bucket[i] ? x - bucket[i] : 0);
            }
            if (tmp + j < ans) ans = tmp + j;
        }
        return ans + at_least;
    }
};