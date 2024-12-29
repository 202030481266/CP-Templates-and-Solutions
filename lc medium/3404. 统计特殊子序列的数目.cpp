#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int s[1001][1001];
// 看着很诡异的题目，以为是dp或者巧妙的数学统计，结果就是枚举，容易选择错误的方法

class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();
        for (int i = n-3; i >= 4; --i) {
            for (int j = i+2; j < n; ++j) {
                int g = gcd(nums[i], nums[j]);
                // x y
                int x = nums[i]/g, y = nums[j]/g;
                s[x][y]++;
            }
        }
        // 0 1 2 3 4.. n-5 n-4 n-3 n-2 n-1
        ll ans = 0;
        for (int i = 2; i <= n-5; ++i) {
            for (int j = i-2; j >= 0; --j) {
                int g = gcd(nums[i], nums[j]);
                int x = nums[i]/g, y = nums[j]/g;
                // y x x y
                ans += s[x][y];
            }
            if (i+2 <= n-3) {
                int k = i+2;
                for (int j = k+2; j < n; ++j) {
                    int g = gcd(nums[k], nums[j]);
                    int x = nums[k]/g, y = nums[j]/g;
                    s[x][y]--;
                }
            }
        }
        return ans;
    }
};