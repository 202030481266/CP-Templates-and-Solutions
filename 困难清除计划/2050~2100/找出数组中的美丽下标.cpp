class Solution {
public:
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
    vector<int> find_substring(string haystack, string needle) {
        int m = needle.length();
        vector<int> res;
        if (m == 0)
            return res;
        vector<int> p = prefix_function(needle);
        for (int i = 0, k = 0; i < haystack.length(); i++) {
            while (k > 0 && needle[k] != haystack[i])
                k = p[k - 1];
            if (needle[k] == haystack[i])
                ++k;
            if (k == m) {
                k = p[k - 1]; 
                res.push_back(i - m + 1);
            }
        }
        return res;
    }
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> A = find_substring(s, a);
        vector<int> B = find_substring(s, b);
        int i = 0, j = 0;
        vector<int> ans;
        for (int i = 0; i < A.size(); ++i) {
            while (j < B.size() && B[j] < A[i] && A[i] - B[j] > k) ++j;
            if (j == B.size()) break;
            else {
                if (B[j] > A[i]) {
                    if (B[j] - A[i] <= k) ans.push_back(A[i]);
                }
                else {
                    ans.push_back(A[i]);
                }
            }
        }
        return ans;
    }
};