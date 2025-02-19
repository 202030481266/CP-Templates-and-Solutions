#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int longestCommonPrefix(string s, string t) {
        int n = s.size(), m = t.size();
        int i = 0, j = 0;
        while (i < n && j < m && s[i] == t[j]) i++, j++;
        int ans = i;
        if (i == n || j == m) return ans;
        if (i + 1 == n) return ans; // 不可能有提升空间
        int l = (++i), r = j;
        while (l < n && r < m && s[l] == t[r]) l++, r++;
        return r;
    }
};