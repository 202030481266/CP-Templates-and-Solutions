#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


class Solution {
public:
    int getSum(vector<int>& nums) {
        int n = nums.size();
        int max_num = *max_element(nums.begin(), nums.end());
        int MAX_NUM = max_num + 2;  // 确定数组中最大的数字

        vector<long long> sumf(MAX_NUM, 0);  // 记录以某数结尾的上升连续子序列数量之和
        vector<long long> sumg(MAX_NUM, 0);  // 记录以某数结尾的下降连续子序列数量之和
        vector<long long> sum_inc(MAX_NUM, 0); 
        vector<long long> sum_dec(MAX_NUM, 0);

        long long total = 0;  // 最终结果

        for (int a : nums) {
            long long f = 1;  // 初始化为1，表示以当前数字a结尾的上升连续子序列数量
            if (a - 1 >= 0 && a - 1 < MAX_NUM) {
                f = (f + sumf[a - 1]) % MOD;  // 如果存在a-1，累加上以a-1结尾的上升连续子序列数量
            }

            long long g = 1;  // 初始化为1，表示以当前数字a结尾的下降连续子序列数量
            if (a + 1 < MAX_NUM) {
                g = (g + sumg[a + 1]) % MOD;  // 如果存在a+1，累加上以a+1结尾的下降连续子序列数量
            }

            long long dp_inc = 0, dp_dec = 0;  // 当前以a结尾的子序列的总和值
            if (a - 1 >= 0 && a - 1 < MAX_NUM) {
                dp_inc = (dp_inc + sum_inc[a - 1]) % MOD;  // 累加以a-1结尾的子序列的总和值
            }
            if (a + 1 < MAX_NUM) {
                dp_dec = (dp_dec + sum_dec[a + 1]) % MOD;  // 累加以a+1结尾的子序列的总和值
            }

            ll res = (dp_inc + dp_dec + (f + g - 1) * a % MOD) % MOD;

            total = (total + res) % MOD;  // 更新总和

            sumf[a] = (sumf[a] + f) % MOD;     // 更新sumf
            sumg[a] = (sumg[a] + g) % MOD;     // 更新sumg
            sum_inc[a] = (sum_inc[a] + dp_inc + a * f) % MOD;
            sum_dec[a] = (sum_dec[a] + dp_dec + a * g) % MOD;

        }

        return (int)(total % MOD);
    }
};