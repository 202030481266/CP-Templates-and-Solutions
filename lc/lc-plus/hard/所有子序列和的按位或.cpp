#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


// 相当困难的问题
// 一个very tricky的观察
// 首先可以观察到一个事实：不能突然越过一个位置到达另一个高位
// 对于一个最高位为 i 的数字，其余的数字的最高位都是小于i, 一次相加中不可能突然得到一个数字能够使得最高位为 i + 2，
// 要想得到更高位置的和， 必然存在一次加法，使得和的最高位为 i+1
// 对于这道题而言，就是如此，我们利用这个结论，只需要确定最大的和的最高位是多少，最小和的最低位是多少，中间全都可以取到1，然后尾部全是0。

class Solution {
public:
    long long subsequenceSumOr(vector<int>& nums) {
        ll sum = 0, x = 0;
        for (int v : nums) {
            x |= v;
            sum += v;
        }
        if (sum == 0) return 0;
        ll ans = sum | x;
        int msb = 63 - __builtin_clzll(ans), flag = 0;
        for (int i = 0; i <= msb; ++i) {
            if (ans & (1ll<<i)) flag = 1;
            if (flag) {
                ans |= (1ll<<i);
            }
        }
        return ans;
    }
};