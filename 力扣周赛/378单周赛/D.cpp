class Solution {
    using pii = pair<int, int>;
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();  // n 是偶数
        int l = 0, r = n - 1, pre = -1;
        vector<pii> arr; 
        while (l < r) {
            if (s[l] == s[r]) {
                if (pre == -1) pre = l;
            }
            else {
                if (pre != -1) {
                    // [pre, l) palindromic string
                    arr.emplace_back(pre, l);
                    pre = -1;
                }
            }
            ++l;
            --r;
        }
        if (pre != -1) {
            // [pre, n/2) is also a palindromic string
            arr.emplace_back(pre, n / 2);
        }
        vector cnt(26, vector<int>(n + 1));
        for (int c = 0; c < 26; ++c) {
            for (int i = 0; i < n; ++i) {
                cnt[c][i + 1] = cnt[c][i] + (s[i] - 'a' == c);
            }
        }
        auto check = [&](int x, int y) -> bool {
            // check [x, y) is palindromic string
            if (y <= x) return true;
            if (arr.empty()) return false;
            auto it = lower_bound(arr.begin(), arr.end(), x, [](const pair<int, int> &p, int num){
                return p.first < num;
            });
            if (it != arr.end() && it->first == x) return it->second >= y; // [x, it->second)
            if (it == arr.begin()) return false;
            it = prev(it); 
            return it->second >= y;
        };
        auto check_cnt = [&](int x, int y) -> bool {
            // check [x, y] is cnt same
            for (int c = 0; c < 26; ++c) {
                if (cnt[c][y + 1] - cnt[c][x] != cnt[c][(n - 1) - x + 1] - cnt[c][(n - 1) - y]) {
                    return false;
                }
            }
            return true;
        };
        auto check_enough = [&](int x1, int y1, int x2, int y2) -> bool {
            if (y2 < x2) return true;
            if (y1 < x1) return false;
            for (int c = 0; c < 26; ++c) {
                // can using [x1, y1] construct [x2, y2]
                if (cnt[c][y1 + 1] - cnt[c][x1] < cnt[c][y2 + 1] - cnt[c][x2]) {
                    return false;
                }
            }
            return true;
        };
        // index formula : (n - 1) - i
        vector<bool> ans;
        for (auto& q : queries) {
            int a = q[0], b = q[1], c = q[2], d = q[3];
            int cc = (n - 1) - c, dd = (n - 1) - d;
            if (dd > b || cc < a) {
                // no section
                int l1, r1, l2, r2;
                if (dd > b) l1 = a, r1 = b, l2 = dd, r2 = cc;
                if (cc < a) l1 = dd, r1 = cc, l2 = a, r2 = b;
                // [0, l1), [l1, r1], (r1, l2), [l2, r2], (r2, n / 2)
                if (check_cnt(l1, r1) && check_cnt(l2, r2) && check(0, l1) && check(r1 + 1, l2) && check(r2 + 1, n / 2)) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
            else if ((a <= dd && cc <= b) || (dd <= a && b <= cc)) {
                // include relationship
                int l = min(a, dd), r = max(b, cc);
                if (check_cnt(l, r) && check(0, l) && check(r + 1, n / 2)) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
            else {
                if (a < dd) {
                    if (check_cnt(a, cc) && check_enough(a, b, n - dd, (n - 1) - a) && check_enough(c, d, b + 1, cc) && check(0, a) && check(cc + 1, n / 2))
                        ans.push_back(true);
                    else ans.push_back(false);
                }
                else {
                    if (check_cnt(dd, b) && check_enough(a, b, (n - 1) - b, c - 1) && check_enough(c, d, dd, a - 1) && check(0, dd) && check(b + 1, n / 2))
                        ans.push_back(true);
                    else ans.push_back(false);
                }
            }
        }
        return ans; 
    }
};