class Solution {
public:
    vector<string> splitMessage(string message, int limit) {
        int n = message.size(), ans = -1, len = 0;
        int v[5] = {0, 9, 90, 900, 9000};
        for (int i = 1; i <= 4; ++i) {
            if (ans > 0 || i * 2 + 3 >= limit) break;
            int sum = n;
            for (int j = 1; j <= i && sum > 0; ++j) {
                if (j == i) {
                    int tmp = limit - 2 * i - 3;
                    if (sum % tmp == 0) {
                        // 刚好整除
                        int x = sum / tmp;
                        if (x <= v[i]) ans = x, len = i;
                    } else {
                        int x = sum / tmp + 1;
                        if (x <= v[i]) ans = x, len = i;
                    }
                }
                else sum -= v[j] * (limit - i - j - 3);
            }
        }
        if (ans == -1) return {};
        vector<string> res;
        int p = 0, total = 0, tot = ans;
        for (int i = 1; i < len; ++i) tot += v[i];
        for (int i = 1; i <= len; ++i) {
            if (i == len) {
                for (int j = 1; j < ans; ++j) {
                    string tmp = message.substr(p, limit - len * 2 - 3) + "<" + to_string(++total) + "/" + to_string(tot) + ">";
                    p += limit - i - len - 3;
                    res.emplace_back(tmp);
                }
                string last = message.substr(p, n - p) + "<" + to_string(tot) + "/" + to_string(tot) + ">";
                res.emplace_back(last);
            }
            else {
                for (int j = 1; j <= v[i]; ++j) {
                    string tmp = message.substr(p, limit - i - len - 3) + "<" + to_string(++total) + "/" + to_string(tot) + ">";
                    p += limit - i - len - 3;
                    res.emplace_back(tmp);
                }
            }
        }
        return res;
    }
};