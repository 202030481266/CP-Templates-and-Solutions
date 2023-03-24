// https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
// 数独问题的转换


class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        // 并查集问题，只要处在同行或者同列就可以了
        int n = stones.size();
        int m_row = INT_MIN, m_col = INT_MIN;

        for (auto c : stones) {
            m_row = max(m_row, c[0]);
            m_col = max(m_col, c[1]);
        }

        UnionFind un(n);
        vector<vector<int>> row(m_row + 1);
        vector<vector<int>> col(m_col + 1);

        for (int i = 0; i < n; ++i) {
            for (int u : row[stones[i][0]]) {
                un.unite(i, u);
            }
            for (int u : col[stones[i][1]]) {
                un.unite(i, u);
            }
            row[stones[i][0]].emplace_back(i);
            col[stones[i][1]].emplace_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (un.find(i) == i) ++ans;
        }
        return n - ans;
    }
};