// 启发式合并难题/并查集难题
class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<int> g[n];
        for (auto& c : edges) {
            g[c[0]].push_back(c[1]);
            g[c[1]].push_back(c[0]);
        }
        int id[n], fa[n], siz[n];
        iota(id, id + n, 0);
        iota(fa, fa + n, 0);
        fill(siz, siz + n, 1);
        sort(id, id + n, [&](int x, int y){return vals[x] < vals[y];});
        function<int(int)> find = [&](int x) {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
        };
        int ans = n;
        for (int x : id) {
            int vx = vals[x], fx = find(x);
            for (int y : g[x]) {
                y = find(y);
                if (vals[y] > vx || y == fx) continue;
                if (vals[y] == vx) {
                    ans += siz[y] * siz[fx];
                    siz[fx] += siz[y]; // 统计其中的val==fx的值的个数
                }
                fa[y] = fx;
            }
        }
        return ans;
    }
};