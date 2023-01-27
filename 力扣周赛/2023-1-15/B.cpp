template<typename T>
struct Fenwick_2d {
    // row from 1 to N
    // column from 1 to M
    vector<vector<T>> vec;
    int N, M;

    Fenwick_2d() { N = M = 0; }
    Fenwick_2d(int n, int m) {
        N = n + 1;
        M = m + 1;
        vec.resize(N);
        for (auto& v : vec) v = vector<T>(M, 0);
    }
    int lowbit(int x) { return x & (-x); }
    void update(int x, int y, T val) {
        // a[x][y] += val
        for (int i = x; i < N; i += lowbit(i))
            for (int j = y; j < M; j += lowbit(j))
                vec[i][j] += val;
    }
    T query(int x, int y) {
        // get [1,1] ~ [x, y] matrix sum
        T res = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            for (int j = y; j > 0; j -= lowbit(j))
                res += vec[i][j];
        return res;
    }
};
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        Fenwick_2d<int> tree(n + 1, n + 1);

        for (auto q : queries) {
            tree.update(q[0] + 1, q[1] + 1, 1);
            tree.update(q[2] + 2, q[3] + 2, 1);
            tree.update(q[0] + 1, q[3] + 2, -1);
            tree.update(q[2] + 2, q[1] + 1, -1);
        }
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ans[i][j] = tree.query(i + 1, j + 1);
        return ans;
    }
};