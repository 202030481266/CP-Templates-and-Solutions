#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        // 交换更优
        // (a1+a2)b1 + a2b2 < (a1+a2)b2 + a1b1 -> a2b1 < a1b2
        int n = damage.size();
        for (auto& v : health) {
            v = (v-1)/power + 1;
        }
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j){
            return damage[i] * health[j] < damage[j] * health[i];
        });
        ll ans = 0, sum = accumulate(damage.begin(), damage.end(), 0ll);
        for (int i = n-1; i >= 0; --i) {
            ans += health[ids[i]] * sum;
            sum -= damage[ids[i]];
        }
        return ans;
    }
};