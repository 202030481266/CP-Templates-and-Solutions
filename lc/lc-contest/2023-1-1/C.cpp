class Solution {
public:
    int minimumPartition(string s, int k) {
        int n = s.size();
        auto _k = to_string(k);

        for (int i = 0; i < n; i++) {
            if (k < s[i] - '0') return -1;
        }

        auto check = [&](string a, string b) {
            if (a.size() != b.size()) return a.size() < b.size();
            else return a <= b;
        };

        auto f = [&]() {
            int i = 0, cnt = 0; 
            while (i < n) {
                string temp = s.substr(i, 1);
                while (check(temp, _k)) {
                    ++i;
                    if (i == n) break;
                    else temp += s[i];
                }
                cnt++;
            }
            return cnt;
        };

        // int l = 1, r = k.size();
        // while (l <= r) {
        //     int mid = (l + r )/ 2;
        //     if (f(mid))
        // }
        return f();
    }
};