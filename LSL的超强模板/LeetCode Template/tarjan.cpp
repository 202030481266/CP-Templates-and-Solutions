class TarjanSCC {
private:
    const vector<vector<int>>& edges;
    const vector<vector<int>>& edgesId;
    vector<int> low, dfn, ans;
    int n, ts;
private:    
    void getCuttingEdge_(int u, int parentEdgeId) {
        low[u] = dfn[u] = ++ts;
        for (int i = 0; i < edges[u].size(); i++) {
            int v = edges[u][i];
            int id = edgesId[u][i];
            if (dfn[v] == -1) {
                getCuttingEdge_(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    ans.push_back(id);
                }
            }
            else if (id != parentEdgeId) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
public:
    TarjanSCC(int _n, const vector<vector<int>>& _edges, const vector<vector<int>>& _edgesId):
        edges(_edges), edgesId(_edgesId), low(_n, -1), dfn(_n, -1), n(_n), ts(-1) {}
    vector<int> getCuttingEdge() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                getCuttingEdge_(i, -1);
            }
        }
        return ans;
    }
};