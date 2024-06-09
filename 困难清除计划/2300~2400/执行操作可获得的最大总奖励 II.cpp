#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int maxTotalReward(vector<int>& a) {
        // 观察1：贪心证明：最大的数字必选，假设这个数字就是mx
        // 观察2：一个子问题，如何能够构造出具体的一个数值似乎是更为基本的问题，显然不能贪心解决，考虑动态规划
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(),a.end()),a.end());
        int ans = a.back();
        a.pop_back();
        bitset<50000> dp;//bitset优化，从来没见过可以这样的，不知道这个计算速度有多快
        dp.set(0);
        for (int& v : a) {
            int m = 50000-v;
            dp |= ((dp<<m)>>m)<<v;
        }
        for (int i=ans-1; i >= 0; --i) {
            if (dp.test(i)) {
                ans += i;
                break;
            }
        }
        return ans;
    }
};