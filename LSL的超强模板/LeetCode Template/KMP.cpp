class KMP {
public:
    KMP() {}
    vector<int> prefix_function(string s) {
        vector<int> p(s.length());
        int k = 0;
        for (int i = 1; i < s.length(); i++) {
            while (k > 0 && s[k] != s[i])
                k = p[k - 1];
            if (s[k] == s[i])
                ++k;
            p[i] = k;
        }
        return p;
    }
    int find_substring(string haystack, string needle) {
        int m = needle.length();
        if (m == 0)
            return 0;
        vector<int> p = prefix_function(needle);
        for (int i = 0, k = 0; i < haystack.length(); i++) {
            while (k > 0 && needle[k] != haystack[i])
                k = p[k - 1];
            if (needle[k] == haystack[i])
                ++k;
            if (k == m)
                // k = p[k - 1]， 寻找所有的位置
                return i + 1 - m;
        }
        return -1;
    }
    // 返回第一个匹配项的下标
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (m == 0) {
            return 0;
        }
        vector<int> pi(m);
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && needle[i] != needle[j]) {
                j = pi[j - 1];
            }
            if (needle[i] == needle[j]) {
                j++;
            }
            pi[i] = j;
        }
        for (int i = 0, j = 0; i < n; i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = pi[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == m) {
                return i - m + 1;
            }
        }
        return -1;
    }
};

