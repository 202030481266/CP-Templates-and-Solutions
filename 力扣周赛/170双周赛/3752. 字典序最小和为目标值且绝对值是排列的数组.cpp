#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    bool cmp(int n, long long target) {
        ll sum = 1ll * n * (n + 1) / 2;
        if (sum < abs(target)) return false;
        int t = n % 4;
        if (t == 1 || t == 2) {
            if (target % 2 == 0) return false;
        }
        else {
            if (target & 1) return false;
        }
        return true;
    }
    vector<int> lexSmallestNegatedPerm(int n, long long target) {
        vector<int> ans;
        while (n > 0) {
            if (cmp(n - 1, target + n)) ans.push_back(-n);
            else if (cmp(n - 1, target - n)) ans.push_back(n);
            else return {};
            --n;
            target -= ans.back();
        }
        ranges::sort(ans);
        return ans;
    }
};