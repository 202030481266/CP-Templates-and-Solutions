typedef pair<int, int> pii;
class Solution {
    int n, type[4], p[4], start;
    unordered_set<int> res;
    //  原地，北 东北 东 东南 南 西南 西 西北
    static constexpr int dirs[][9] = {
        {0, 0}, 
        {-1, 0}, 
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1}
    };
public:
    // 因为每一个移动组合选定方向之后后面不能更改，所以后面出现的的位置一定是不相同的
    // 搜索深度绝对不会超过8层
    void dfs(int pos, int d) {
        res.emplace(pos);
        if (d == 0) return;
        vector<pii> tmp;
        build(0, pos, d, 0, 0, tmp);
        for (auto [u, v] : tmp) {
            dfs(u, v);
        }
    }
    void build(int dep, int s, int d, int ns, int nd, vector<pii>& v) {
        if (dep == n) {
            v.emplace_back(ns, nd);
            return;
        }
        int pos = (s / p[dep]) % 64;
        int dir = ((d >> (4 * dep)) & 15);
        // 已经终止了 或者 变为终止的状态
        // 但是这里有一个很大的坑： 无论你停不停都要检查别人是否到了这里
        int flag = 1;
        for (int i = 0; i < dep; ++i) {
            if ((ns / p[i]) % 64 == pos) {
                flag = 0;
                break;
            }
        }
        if (flag)
            build(dep + 1, s, d, ns + p[dep] * pos, nd, v);
        if (dir > 0) {
            int nx = (pos / 8) + dirs[dir][0], ny = (pos % 8) + dirs[dir][1];
            if (nx >= 0 && ny >= 0 && nx < 8 && ny < 8) {
                int id = nx * 8 + ny;
                for (int i = 0; i < dep; ++i) 
                    if ((ns / p[i]) % 64 == id) return;
                build(dep + 1, s, d, ns + id * p[dep], nd | (dir << (4 * dep)), v);
            }
        }
    }
    void solve(int dep, int d) {
        if (dep == n) {
            dfs(start, d);
            return;
        }
        if (type[dep] == 1) {
            for (int i = 1; i < 9; i += 2) 
                solve(dep + 1, d | (i << (dep * 4)));
        }
        else if (type[dep] == 2) {
            for (int i = 1; i < 9; ++i)
                solve(dep + 1, d | (i << (dep * 4)));
        }
        else {
            for (int i = 2; i < 9; i += 2)
                solve(dep + 1, d | (i << (dep * 4)));
        }
    }
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        p[0] = 1;
        for (int i = 1; i < 4; ++i) p[i] = p[i - 1] * 64;
        n = pieces.size();
        for (int i = 0; i < n; ++i) {
            if (pieces[i] == "rook") type[i] = 1;
            else if (pieces[i] == "queen") type[i] = 2;
            else type[i] = 3;
            int x = positions[i][0] - 1, y = positions[i][1] - 1;
            start += p[i] * (x * 8 + y);
        }
        solve(0, 0);
        return res.size();
    }
};