#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


// 对于一个子数组来说，越长，GCD可能就越小，并且每一次变小起码除以2

class Solution {
public:
    int minimumSplits(vector<int>& nums) {
        int n = nums.size();
        int ans = 0, g = 0;
        for (int v : nums) {
            if (g == 0 || gcd(g, v) == 1) {
                ++ans;
                g = v;
            }
            else g = gcd(g,v);
        }
        return ans;
    }
};