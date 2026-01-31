class Solution {
public:
    string makeAntiPalindrome(string s) {
        int n = s.size();

        vector<int> cnt(26);
        for (char& ch : s) ++cnt[ch - 'a'];
        for (int i = 0; i < 26; ++i)
            if (cnt[i] > n / 2) return "-1"; 
        vector<int> ans(n);
        for (int i = 0, j = 0; i < 26 && j < n / 2; ++i)
            if (cnt[i])
                while (cnt[i] && j < n / 2) {
                    ans[j++] = i;
                    --cnt[i];
                }
        for (int i = n / 2; i < n; ++i) {
            for (int j = 0; j < 26; ++j)
                if (cnt[j] && ans[n - 1 - i] != j) {
                    --cnt[j];
                    ans[i] = j;
                    break;
                }
        }
        string res;
        for (int& v : ans) res.push_back((char)(v + 'a'));
        return res;
    }
};