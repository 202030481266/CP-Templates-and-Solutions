#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        vector<int> cnt(1<<11, 0), res(1<<11, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                cnt[nums[i] ^ nums[j]]++;
            }
        }
        int ans = 0;
        for (int i = 0; i < (1<<11); ++i) {
            if (cnt[i]) {
                for (int j = 0; j < n; ++j) {
                    int x = nums[j] ^ i;
                    if (!res[x]) {
                        ++ans;
                        res[x] = 1;
                    }
                }
            }
        }
        return ans;
    }
};