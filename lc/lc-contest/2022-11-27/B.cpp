class Solution {
public:
    int appendCharacters(string s, string t) {
        int n = s.size(), m = t.size();
        int l = 0, r = 0;
        while (l < n && r < m) {
            while (l < n && s[l] != t[r]) ++l;
            if (l == n) break;
            ++r, ++l;
        }
        return m - r;
    }
};