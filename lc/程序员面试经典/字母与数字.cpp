class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        int n = array.size();
        unordered_map<int, int> a;
        vector<int> f(n + 1);

        for (int i = 1; i <= n; ++i) {
            f[i] = f[i - 1] + (int)(isdigit(array[i - 1][0]));
        }
        a[0] = 0;
        int ans = 0, index = 0;
        for (int i = 1; i <= n; ++i) {
            int x = 2 * f[i] - i;
            if (a.count(x)) {
                if ((i - a[x]) & 1) continue;
                if (ans < i - a[x] || (ans == i - a[x] && a[x] < index))
                    ans = i - a[x], index = a[x];
            }
            else a[x] = i;
        }
        vector<string> res;
        for (int i = index; i <= index + ans - 1; ++i)
            res.emplace_back(array[i]);
        return res;
    }
};