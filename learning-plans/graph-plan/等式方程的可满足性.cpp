class Solution {
    int fa[26];
public:
    int find(int x) {
        return fa[x] != x ? fa[x] = find(fa[x]) : x;
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        fa[fx] = fy;
    }
    bool equationsPossible(vector<string>& equations) {
        int n = equations.size();
        iota(fa, fa + 26, 0);
        for (string& s : equations) {
            if (s[1] == '=') {
                merge(s[0] - 'a', s[3] - 'a');
            }
        }
        for (string& s : equations) {
            if (s[1] == '!') {
                if (find(s[0] - 'a') == find(s[3] - 'a')) {
                    return false;
                }
            }
        }
        return true;
    }
};