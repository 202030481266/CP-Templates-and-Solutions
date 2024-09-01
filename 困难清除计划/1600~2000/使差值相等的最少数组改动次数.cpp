#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


int cnt[100005];
class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        // abs(a[i]-a[n-1-i])==X
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n/2; ++i) {
            int x = nums[i], y = nums[n-1-i], c=abs(x-y);
            int mx = max(max(x,y), max(k-x,k-y));
            // [0,c), (c,mx], (mx, k]
            if (c > 0) {
                ++cnt[0];
                --cnt[c];
            }
            if (mx > c) {
                ++cnt[c+1];
                --cnt[mx+1];
            }
            if (k > mx) 
                cnt[mx+1]+=2;
        }
        int ans = inf, sum = 0;
        for (int i = 0; i <= k; ++i) {
            sum += cnt[i];
            if (sum < ans) ans = sum;
        }
        return ans;
    }

};