// 技巧： 交换的方案选择对应了不同的代价，可以使用一个全局最小值进行交换，非常灵活
// 下面是大佬写的代码，非常精巧

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> diff;
        for (auto x : basket1) 
            diff[x]++;
        for (auto x : basket2) 
            diff[x]--;
        for (auto &[x, y] : diff) 
            if (y & 1) 
                return -1;
        vector<int> a, b;
        for (auto x : basket1) {
            if (diff[x] > 0) {
                a.push_back(x);
                diff[x] -= 2;
            }
        }
        for (auto x : basket2) {
            if (diff[x] < 0) {
                b.push_back(x);
                diff[x] += 2;
            }
        }
        // 两种策略
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<int>());
        int z = min(*min_element(basket1.begin(), basket1.end()), *min_element(basket2.begin(), basket2.end()));
        long long res = 0;
        for (int i = 0; i < a.size(); i++) {
            res += min(min(a[i], b[i]), 2 * z);
        }
        return res;
    }
};

