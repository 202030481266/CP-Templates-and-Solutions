class Solution {
public:
    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }

    string prettyPrint(vector<string> list, int length = -1) {
        if (length == -1) {
            length = list.size();
        }

        if (length == 0) {
            return "[]";
        }

        string result;
        for(int index = 0; index < length; index++) {
            result += list[index] + ", ";
        }
        return "[" + result.substr(0, result.length() - 2) + "]";
    }

    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        unordered_map<string, vector<pair<int, string>>> vis;

        int n = username.size();
        for (int i = 0; i < n; ++i) {
            vis[username[i]].push_back({timestamp[i], website[i]});
        }
        unordered_map<string, int> pattern;
        for (auto& [_, web] : vis) {
            sort(web.begin(), web.end());
            unordered_set<string> user;
            for (int i = 2; i < web.size(); ++i) {
                for (int j = i - 1; j >= 0; --j) {
                    for (int k = j - 1; k >= 0; --k) {
                        string pa = web[k].second + "_" + web[j].second + "_" + web[i].second;
                        user.insert(pa);
                    }
                }
            }
            for (string p : user) pattern[p] += 1;
        }
        vector<string> mx;
        int cnt = 0;
        for (auto [p, t] : pattern) {
            string str = p;
            vector<string> cur = split(str, '_');
            assert(cur.size()==3);
            if (t > cnt) {
                cnt = t;
                mx = cur;
            }
            else if (t == cnt && cur < mx) mx = cur;
        }
        return mx;
    }
};