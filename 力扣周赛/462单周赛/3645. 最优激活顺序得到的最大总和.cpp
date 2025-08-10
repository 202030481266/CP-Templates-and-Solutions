#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        int n = value.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        ranges::sort(ids, [&](int i, int j){
            return limit[i] == limit[j] ? value[i] > value[j] : limit[i] < limit[j];
        });
        int i = 0, k = 0;
        ll ans = 0;
        while (i < n) {
            int j = i + 1;
            k = limit[ids[i]];
            while (j < n && limit[ids[i]] == limit[ids[j]]) ++j;
            for (int x = i; x < min(i + k, j); ++x) {
                ans += value[ids[x]];
            }
            i = j;
        }
        return ans;
    }
};