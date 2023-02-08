class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string,list<int>> a;
        unordered_map<string, bool> vis;
        vector<pair<int,string>> b;
        vector<string> ans;

        int n = keyName.size();
        for (int i = 0; i < n; ++i) {
            string s_hour = keyTime[i].substr(0, 2);
            string s_minute = keyTime[i].substr(3, 2);
            int hour = stoi(s_hour);
            int minute = stoi(s_minute);
            b.emplace_back(make_pair(hour * 60 + minute, keyName[i]));
        }
        sort(b.begin(), b.end());
        for (auto c : b) {
            if (vis[c.second]) continue;
            if (!a.count(c.second)) {
                a[c.second].emplace_back(c.first);
            } else {
                if (a[c.second].size() < 2) {
                    a[c.second].emplace_back(c.first);
                    if (a[c.second].size() == 2) {
                        if (a[c.second].front() + 60 < a[c.second].back()) a[c.second].pop_front();
                    }
                } else {
                    if (a[c.second].front() + 60 >= c.first) {
                        ans.emplace_back(c.second);
                        vis[c.second] = true;
                    } else {
                        a[c.second].pop_front();
                        a[c.second].emplace_back(c.first);
                    }
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};