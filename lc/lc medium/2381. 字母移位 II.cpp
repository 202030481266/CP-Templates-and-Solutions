#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int> sum(n+1);
        
        for (auto& s : shifts) {
            int l = s[0], r = s[1], val = s[2] ? 1 : -1;
            sum[r+1] -= val;
            sum[l] += val;
        }

        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += sum[i];
            int p = (s[i] - 'a' + cnt % 26 + 26) % 26;
            s[i] = 'a' + p;
        }
        return s;
    }
};