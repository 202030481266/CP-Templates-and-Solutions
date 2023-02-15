class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> hs;
        vector<string> ans;

        int n = s.size();
        if (n <= 10) return ans;

        for (int i = 0; i + 9 < n; ++i) {
            string t = s.substr(i, 10);
            ++hs[t];
            if (hs[t] == 2) ans.emplace_back(t);
        }
        return ans;
    }
};