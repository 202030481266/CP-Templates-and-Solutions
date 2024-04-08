int fa[100010];
int w[100010];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y, int cost) {
    int fx = find(x), fy = find(y);
    if (fx == fy) {
        w[fx] &= cost;
        return;
    }
    fa[fx] = fy;
    w[fy] = w[fy] & cost & w[fx];
}
class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        iota(fa, fa + n, 0);
        for (int i = 0; i < n; ++i) 
            w[i] = INT_MAX;
        for (auto& e : edges) {
            int u = e[0], v = e[1], c = e[2];
            merge(u, v, c);
        }
        vector<int> ans;
        for (auto& q : query) {
            int s = q[0], t = q[1];
            if (find(s) != find(t)) ans.push_back(-1);
            else {
                if (s == t) ans.push_back(0);
                else ans.push_back(w[find(s)]);
            }
        }
        return ans;
    }
};