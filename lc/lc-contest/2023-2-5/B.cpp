class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int n = words.size();
        vector<int> sum(n + 1);

        auto f = [&](char ch) {
            return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
        };

        for (int i = 1; i <= n; ++i) {
            int k = words[i - 1].size();
            sum[i] = sum[i - 1];
            if (f(words[i - 1][0]) && f(words[i - 1][k - 1])) sum[i] += 1;
        }
        vector<int> ans;
        for (auto c : queries) {
            ans.emplace_back(sum[c[1] + 1] - sum[c[0]]);
        }
        return ans;
    }
};