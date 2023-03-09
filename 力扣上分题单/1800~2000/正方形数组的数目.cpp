// https://leetcode.cn/problems/number-of-squareful-arrays/
// 图论 + 寻找哈密顿路径，使用dfs暴力搜会超时，用图就是为了防止大量同样的数字从而超时


class Solution {
public:
    bool isSquare(int n) {
        int t = sqrt(n);
        return t * t == n;
    }
    void dfs(const vector<int>& nodes, const vector<vector<int> >& g, 
            map<int, int>& counts, int i, int m, int M, int& res) {
        if (m == M) {
            ++res;
            return;
        }
        for (auto j : g[i]) {
            if (counts[nodes[j]] > 0) {
                --counts[nodes[j]];
                dfs(nodes, g, counts, j, m + 1, M, res);
                ++counts[nodes[j]];
            }
        }
    }
    int numSquarefulPerms(vector<int>& A) {
        map<int, int> counts;
        for (auto x : A) {
            ++counts[x];
        }
        vector<int> nodes;
        for (auto& p : counts) {
            nodes.push_back(p.first);
        }
        int N = nodes.size();
        vector<vector<int> > g(N);
        for (int i = 0; i < N; ++i) {
            if (counts[nodes[i]] > 1 && isSquare(nodes[i] * 2)) {
                g[i].push_back(i);
            }
            for (int j = i + 1; j < N; ++j) {
                if (isSquare(nodes[i] + nodes[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < N; ++i) {
            --counts[nodes[i]];
            dfs(nodes, g, counts, i, 1, A.size(), res);
            ++counts[nodes[i]];
        }
        return res;
    }
};

