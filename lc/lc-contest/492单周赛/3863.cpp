#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        if (n == 1) return 0;
        if (n == 2) {
            if (s[1] < s[0]) return -1;
            return 0;
        }
        if (is_sorted(s.begin(), s.end())) return 0;
        string x = s;
        sort(x.begin(), x.begin() + n - 1);
        if (is_sorted(x.begin(), x.end())) return 1;
        x = s;
        sort(x.begin() + 1, x.end());
        if (is_sorted(x.begin(), x.end())) return 1;
        x = s;
        sort(x.begin(), x.begin() + n - 1);
        sort(x.begin() + 1, x.end());
        if (is_sorted(x.begin(), x.end())) return 2;
        x = s;
        sort(x.begin() + 1, x.end());
        sort(x.begin(), x.begin() + n - 1);
        if (is_sorted(x.begin(), x.end())) return 2;
        return 3;
    }
};