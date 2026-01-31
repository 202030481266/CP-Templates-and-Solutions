class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        int n = s.size();
        vector<int> cnt(26);
        int l = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            int t = s[i] - 'a';
            ++cnt[t];
            while (cnt[t] > 1 || i - l + 1 > k) {
                --cnt[s[l++] - 'a'];
            }
            if (i - l + 1 == k) ++ans;
        }
        return ans;
    }
};