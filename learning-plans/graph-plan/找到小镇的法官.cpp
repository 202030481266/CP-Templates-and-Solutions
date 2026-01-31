class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> in(n), out(n);
        for (auto& e : trust) {
            ++in[e[1] - 1];
            ++out[e[0] - 1];
        }
        for (int i = 0; i < n; ++i) {
            if (in[i] == n - 1 && out[i] == 0) {
                return i + 1;
            }
        }
        return -1;
    }
};