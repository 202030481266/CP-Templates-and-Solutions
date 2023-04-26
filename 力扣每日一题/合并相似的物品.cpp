class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        vector<int> w(1010, 0);

        set<int> s;
        for (auto c : items1)
            w[c[0]] += c[1], s.emplace(c[0]);
        for (auto c : items2)
            w[c[0]] += c[1], s.emplace(c[0]);
        vector<vector<int>> ans;

        for (auto it = s.begin(); it != s.end(); ++it)
            ans.emplace_back(vector<int>{*it, w[*it]});
        return ans;
    }
};