class Solution {
public:
    // 二分 + 枚举
    int minGroupsForValidAssignment(vector<int>& balls) {
        int n = balls.size();
        unordered_map<int, int> cnt;
        unordered_map<int, int> h;

        for (int& v : balls) cnt[v] += 1;
        
        vector<int> a;
        for (auto& kv : cnt) {
            a.push_back(kv.second); // 有多少种类的数字
            h[kv.second] += 1;  // 出现次数对应的种类数
        }

        // 明显最大的盒子容量越大，使用的盒子会越少，也就是说总是不输的，并且对于容量越小就越有可能有方案，但是会出现一个突变，那就是选择数量本身自己为容量
        // 对于一个容量 k 来说，我们需要讨论对于数字 x 来说如何拆分使用最少的盒子，res = (x - 1) / k + 1
        // 找到最大的公共容量

        auto check = [&](int k) -> bool {
            for (int& v : a) {
                int t = (k - v % k) % k;
                if (1ll * t * (k - 1) > v) return false;
            }
            return true;
        };

        int l = 1, r = *max_element(a.begin(), a.end()) + 1;

        // 对于所有的数字都可用的一个容量
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }

        for (auto& kv : cnt) 
            if (h[kv.second] + h[kv.second - 1] == a.size())
                l = max(l, kv.second);

        int ans = 0;
        for (int& v : a) ans += (v - 1) / l + 1;
        return ans;
    }
};