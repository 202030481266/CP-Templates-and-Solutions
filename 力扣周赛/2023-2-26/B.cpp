class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        int n = word.size();

        long long cur = 0;
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            cur = (cur * 10 + word[i] - '0') % m;
            ans.emplace_back((cur == 0 ? 1 : 0));
        }
        return ans;
    }
};