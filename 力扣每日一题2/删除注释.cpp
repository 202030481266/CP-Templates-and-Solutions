class Solution {
public:
    // 状态自动机
    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }
    vector<string> removeComments(vector<string>& source) {
        int n = source.size();
        int sta = 0;
        string s;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < source[i].size(); ++j) {
                if (sta == 0) {
                    if (source[i][j] == '/') {
                        if (j + 1 < source[i].size() && source[i][j + 1] == '/') {
                            ++j;
                            sta = 1; // row comment
                        }
                        else if (j + 1 < source[i].size() && source[i][j + 1] == '*') {
                            ++j;
                            sta = 2;
                        }
                        else {
                            s.push_back(source[i][j]);
                        }
                    }
                    else { 
                        s.push_back(source[i][j]);
                    }
                }
                else if (sta == 1) {
                    break;
                }
                else {
                    if (source[i][j] == '*') {
                        if (j + 1 < source[i].size() && source[i][j + 1] == '/') {
                            ++j;
                            sta = 0;
                        }
                    }
                }
            }
            if (sta == 0) {
                if (i < n - 1)
                    s.push_back('$');
            }
            else if (sta == 1) {
                sta = 0;
                if (i < n - 1)
                    s.push_back('$');
            }
        }
        auto k = split(s, '$');
        vector<string> ans;
        for (auto& c : k) if (c.size()) ans.push_back(c);
        return ans;
    }
};
