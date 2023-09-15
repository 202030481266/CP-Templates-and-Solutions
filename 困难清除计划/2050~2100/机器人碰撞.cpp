class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size(), id[n];
        iota(id, id + n, 0);
        sort(id, id + n, [&](int i, int j){
            return positions[i] < positions[j];
        });
        stack<int> s;
        vector<pair<int,int>> ans;
        for (int i = 0; i < n; ++i) {
            int k = id[i];
            if (directions[k] == 'R') {
                s.push(k);
            }
            else {
                int cur = healths[k];
                while (!s.empty() && healths[s.top()] <= cur) {
                    if (healths[s.top()] == cur) cur = 0;
                    else --cur;
                    s.pop();
                }
                if (cur > 0) {
                    if (s.empty()) {
                        ans.emplace_back(k, cur);
                    }
                    else {
                        --healths[s.top()];
                    }
                }
            }
        }
        while (!s.empty()) {
            ans.emplace_back(s.top(), healths[s.top()]);
            s.pop();
        }
        sort(ans.begin(), ans.end());
        vector<int> res;
        for (auto& p : ans) res.push_back(p.second);
        return res;
    }
};