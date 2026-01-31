#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    long long numberOfSubstrings(string s, int k) {
        int n = s.size();
        ll ans = 0;
        
        vector<int> cnt(26);

        int l = 0, cur = 0;
        for (int i = 0; i < n; ++i) {
            cnt[s[i]-'a']++;
            if (cnt[s[i]-'a'] == k) ++cur;
            while (cur) {
                --cnt[s[l]-'a'];
                if (cnt[s[l]-'a'] == k-1) --cur;
                ++l;
            }
            ans += l;
        }

        return ans;
    }
};
