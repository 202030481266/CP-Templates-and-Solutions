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
    string mergeCharacters(string s, int k) {
        int n = s.size();
        vi last(26, -1);
        string ans;
        int p = 0;
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (last[c] == -1 || p - last[c] > k) {
                ans.push_back(s[i]);
                ++p;
                last[c] = p - 1;
            }
        }
        return ans;
    }
};