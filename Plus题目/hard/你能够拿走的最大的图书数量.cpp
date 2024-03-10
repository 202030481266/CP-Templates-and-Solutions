// 线性的解法
class Solution {
public:
    long long maximumBooks(vector<int>& books) {
        // 单调栈
        int n = books.size();
        stack<pair<int, int>> s; 

        long long ans = 0, x, res = LONG_LONG_MIN;
        for (int i = 0; i < n; ++i) {
            x = 1ll;
            while (!s.empty() && s.top().first > books[i] - x) {
                ans -= (s.top().first * 2ll - s.top().second + 1) * s.top().second / 2;
                x += s.top().second;
                s.pop();
            }
            if (x > books[i]) x = books[i]; // check 
            if (books[i] > 0) {
                s.emplace(books[i], x);
                ans += (books[i] * 2ll - x + 1) * x / 2;
            }
            res = max(res, ans);
        }
        return res;
    }
};