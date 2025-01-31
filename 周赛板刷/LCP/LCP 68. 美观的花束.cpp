#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int beautifulBouquet(vector<int>& flowers, int k) {
        int n = flowers.size(), mx = *max_element(flowers.begin(), flowers.end());
        vector<int> cnt(mx+1, 0);
        int l = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            cnt[flowers[i]]++;
            while (cnt[flowers[i]] > k) {
                cnt[flowers[l++]]--;
            }
            ans = (ans + (i - l + 1)) % mod;
        }
        return ans;
    }
}; 