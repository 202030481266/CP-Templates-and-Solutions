// 卡三次方，需要使用哈希表
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size(), ans = 0;
        unordered_map<string, int> cnt;
        for (int i = 0; i < n; ++i) {
            string s, t;
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j]) s.push_back('1'), t.push_back('0');
                else s.push_back('0'), t.push_back('1');
            }
            ++cnt[s];
            ans = max(ans, cnt[s] + cnt[t]);
        }
        return ans;
    }
};