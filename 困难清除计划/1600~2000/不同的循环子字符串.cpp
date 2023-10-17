class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size(), lcp[n + 1][n + 1];
        memset(lcp, 0, sizeof(lcp));

        // LCP
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) 
                if (text[i - 1] == text[j - 1]) lcp[i][j] = lcp[i - 1][j - 1] + 1;
        unordered_set<string> h;
        for (int i = 1; i <= n; ++i) 
            for (int j = i - 1; j >= i - j; --j)
                if (lcp[i][j] >= i - j && !h.count(text.substr(j, i - j))) h.insert(text.substr(j, i - j));
        return h.size();
    }
};