#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 排序的考虑很妙，思维量很大的题目
// 也有考虑最大值和次大值的方法，这个本质上是一种优化，因为排序可以过掉就不需要考虑更难的算法

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& pairs) {
        int m = pairs.size();
        for (auto&p : pairs) {
            if (p[1] < p[0]) swap(p[1], p[0]);
        }
        // 每一个区间的贡献本质上等于 [last, r)关于left的等差数列求和, left是前面的区间的左端点子最大值
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
        });
        vector<long long> arr(m+1);
        vector<int> changeleft;
        int left = 0, last = 1;
        long long sum = 0;
        for (int i = 0; i < m; ++i) {
            // [last, pairs[i][1])
            // [last-left, pairs[i][1]-left)
            arr[i] = 1ll * (last - left + pairs[i][1] - left - 1) * (pairs[i][1] - last) / 2;
            sum += arr[i];
            if (pairs[i][0] >= left) {
                changeleft.push_back(i);
                left = pairs[i][0];
            }
            last = pairs[i][1];
        }
        // [last, n+1)
        arr[m] = 1ll * (last - left + n - left) * (n - last + 1) / 2;
        sum += arr[m];
        ll ans = sum;
        int N = changeleft.size();
        for (int i = 0; i < N; ++i) {
            left = (i == 0 ? 0 : pairs[changeleft[i-1]][0]);
            last = pairs[changeleft[i]][1];
            ll cur = sum;
            for (int j = changeleft[i] + 1; j < (i == N-1 ? m : changeleft[i+1] + 1); ++j) {
                cur -= arr[j];
                // [last, pairs[j][1])
                cur += 1ll * (last - left + pairs[j][1] - left - 1) * (pairs[j][1] - last) / 2;
                left = max(left, pairs[j][0]);
                last = pairs[j][1];
            }
            if (i == N-1) {
                cur -= arr[m];
                cur += 1ll * (last - left + n - left) * (n - last + 1) / 2;
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};