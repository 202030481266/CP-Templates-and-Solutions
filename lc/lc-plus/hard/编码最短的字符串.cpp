class Solution {
public:
    string encode(string s) {
        int n = s.size();
        vector f(n, vector<string>(n));

        auto parse = [&](string& str, int p) -> pair<int, string> {
            int m = str.size();
            string rep = str.substr(p + 1, m - p - 2); // [p + 1, m - 1)
            string num = str.substr(0, p); // [0, p)
            return {stoi(num), rep};
        };

        auto check = [&](string& str) -> pair<bool, int> { // num[rep]
            // 这个检查算是最核心的点了，错了两次判断
            int p = 0;
            while (p < str.size() && str[p] != '[') ++p;
            if (p == str.size() || !isdigit(str[0]) || str.back() != ']') 
                return {true, -1};
            int cnt = 0;
            for (int i = p; i < str.size() - 1; ++i) {
                if (str[i] == '[') ++cnt;
                else if (str[i] == ']') --cnt;
                if (cnt == 0) return {true, -1};
            }
            return {false, p};
        };

        auto merge = [&](string& s1, string& s2) -> string {
            auto x = check(s1);
            auto y = check(s2);
            bool flag1 = x.first, flag2 = y.first;
            int p1 = x.second, p2 = y.second;
            if (flag1 && flag2) {
                // 两个都是不可整体重复的字符串
                string res = s1 + s2;
                // 需要找到最短的循环节
                int m = res.size(), flag = 1;
                for (int len = 1; len < m; ++len) {
                    if (m % len) continue;
                    flag = 1;
                    // [0, len - 1)
                    for (int i = 0; i < len && flag; ++i) {
                        for (int j = i + len; j < m && flag; j += len) {
                            if (res[j] != res[i]) flag = 0;
                        }
                    }
                    if (flag) {
                        string tmp = to_string(m / len) + "[" + res.substr(0, len) +  "]";
                        return tmp.size() < res.size() ? tmp : res;
                    }
                }
                return res;
            }
            else if (flag1) {
                // s1是一个不可整体合并的字符串, s2是一个编码字符串
                // [p2 + 1, m - 1), 重复的编码串，[0, p2)数字重复次数
                auto r = parse(s2, p2);
                if (r.second == s1) {
                    return to_string(r.first + 1) + "[" + r.second + "]";
                }
                return s1 + s2;
            }
            else if (flag2) {
                // s2是一个不可整体合并的字符串，s1是一个编码字符串
                auto r = parse(s1, p1);
                if (r.second == s2) {
                    return to_string(r.first + 1) + "[" + r.second + "]";
                }
                return s1 + s2;
            }
            else {
                // s1,s2都是一个编码字符串
                auto r1 = parse(s1, p1);
                auto r2 = parse(s2, p2);
                if (r1.second == r2.second) {
                    return to_string(r1.first + r2.first) + "[" + r1.second + "]";
                }
                return s1 + s2;
            }
        };

        function<string(int, int)> dfs = [&](int i, int j) -> string {
            if (f[i][j].size() != 0) return f[i][j];
            string& r = f[i][j];
            r = s.substr(i, j - i + 1);
            if (j - i + 1 <= 4) return r;
            for (int k = i; k < j; ++k) {
                string left = dfs(i, k);
                string right = dfs(k + 1, j);
                string result = merge(left, right);
                if (result.size() < r.size()) 
                    r = result;
            }
            return r;
        };

        return dfs(0, n - 1);
    }
};