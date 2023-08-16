class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int n = indices.size();
        vector<bool> use(s.size());
        vector<string> a(s.size());
        for (int i = 0; i < n; ++i) {
            int r = indices[i] + sources[i].size(); // [l, r)
            if (r > s.size()) continue;
            if (s.substr(indices[i], sources[i].size()) == sources[i]) {
                use[indices[i]] = true;
                a[indices[i]] = targets[i];
            }
        }
        string ans;
        for (int i = 0; i < s.size(); ++i) {
            if (use[i]) {
                ans += a[i];
                i += a[i].size() - 1;
            }
            else {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};