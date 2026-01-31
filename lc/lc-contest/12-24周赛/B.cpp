class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = s.size();
        vector<vector<int>> sum(n + 1, vector<int>(3, 0));

        for (int i = 1; i <= s.size(); i++) {
            sum[i][0] = sum[i - 1][0] + (s[i - 1] == 'a'); 
            sum[i][1] = sum[i - 1][1] + (s[i - 1] == 'b'); 
            sum[i][2] = sum[i - 1][2] + (s[i - 1] == 'c'); 
        }
        if (sum[n][0] < k || sum[n][1] < k || sum[n][2] < k) return -1;

        auto f = [&](int v) {
            for (int i = 0; i <= v; i++) {
                int j = v - i;
                int c_a = sum[i][0] + sum[n][0] - sum[n - j][0];
                int c_b = sum[i][1] + sum[n][1] - sum[n - j][1];
                int c_c = sum[i][2] + sum[n][2] - sum[n - j][2];
                if (c_a >= k && c_b >= k && c_c >= k) return true;
            }
            return false;
        };

        int l = k * 3, r = s.size(), ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (f(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
};