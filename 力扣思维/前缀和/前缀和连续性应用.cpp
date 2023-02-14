// https://leetcode.cn/problems/longest-well-performing-interval/
// 单调栈也可以做并且很灵活，但是利用前缀和连续性更加简单
// 前缀和开始是0，如果 s[i] <= 0, 那么前面如果有解就必然经过一个值 s[i]-1，
// 并且要想算出比 s[i]-1 更小的数也必须先算出 s[i]-1，所以 s[i]-1 是最优的


class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();

        for (int i = 0; i < n; ++i)
            hours[i] = (hours[i] > 8) ? 1 : -1;

        vector<int> sum(n + 1);
        unordered_map<int,int> a;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + hours[i];
            if (!a.count(sum[i])) a[sum[i]] = i;
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (sum[i]) ans = max(ans, i);
            else {
                // try to find s[i] - 1
                if (a.count(sum[i] - 1)) 
                    ans = max(ans, i - a[sum[i] - 1]);
            }
        }
        return ans;
    }
};