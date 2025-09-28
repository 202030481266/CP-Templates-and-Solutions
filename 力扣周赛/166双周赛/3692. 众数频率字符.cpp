#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    string majorityFrequencyGroup(string s) {
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a']++;
        int mx = *max_element(cnt.begin(), cnt.end());
        int n = s.size();
        vector pos(mx + 1, vector<int>{});
        for (int i = 0; i < 26; ++i) {
            if (cnt[i]) {
                pos[cnt[i]].push_back(i);
            }
        }
        int sz = 0;
        for (int i = 1; i <= mx; ++i) {
            if (pos[i].size() >= pos[sz].size()) sz = i;
        }
        string ans;
        for (char c : pos[sz]) ans.push_back(static_cast<char>(c + 'a'));
        return ans;
    }
};