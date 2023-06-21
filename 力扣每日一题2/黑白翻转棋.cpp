class Solution {
    typedef unsigned long long ull;
    typedef pair<int, int> pii;
    static constexpr int dirs[8][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
public:
    int flipChess(vector<string>& chessboard) {
        int n = chessboard.size(), m = chessboard[0].size(); 
        int f[n][m], cur[n][m];
        ull init = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (chessboard[i][j] == '.') f[i][j] = 2;
                else if (chessboard[i][j] == 'X') f[i][j] = 1, init |= (1ULL << (i * m + j));  // black
                else f[i][j] = 0; // white
            }
        function<vector<pii>(int, int, int, int)> get_one = [&](int x, int y, int dx, int dy) -> vector<pii> {
            vector<pii> p;
            int i, j;
            for (i = x + dx, j = y + dy; i >= 0 && i < n && j >= 0 && j < m; i += dx, j += dy) {
                if (cur[i][j] == 2) return vector<pii>{};
                else if (cur[i][j] == 0) p.emplace_back(i, j);  // get white
            }
            i -= dx, j -= dy;  // 最后一个点
            if (cur[i][j] != 1) return vector<pii>{};
            return p;
        };
        function<vector<pii>(int, int , int, int)> get_edge_one = [&](int x, int y, int dx, int dy) -> vector<pii> {
            vector<pii> p;
            int len = 0;
            for (int i = x + dx, j = y + dy, k = 1; i >= 0 && i < n && j >= 0 && j < m; i += dx, j += dy, ++k) {
                if (cur[i][j] == 2) break;
                else if (cur[i][j] == 1) len = k;
            }
            for (int i = 1; i <= len; ++i) 
                if (cur[x + dx * i][y + dy * i] == 0)
                    p.emplace_back(x + dx * i, y + dy * i);
            return p;
        };
        function<vector<pii>(int, int)> get = [&](int r, int c) -> vector<pii> {
            // 检查八个方向
            vector<pii> pos;
            for (int i = 0; i < 8; ++i) {
                auto res = get_one(r, c, dirs[i][0], dirs[i][1]); 
                for (auto c : res) pos.emplace_back(c);
            }
            return pos;
        };
        function<vector<pii>(int, int)> get_edge = [&](int r, int c) -> vector<pii> {
            vector<pii> pos;
            for (int i = 0; i < 8; ++i) {
                auto res = get_edge_one(r, c, dirs[i][0], dirs[i][1]);
                for (auto c : res) pos.emplace_back(c);
            }
            return pos;
        };
        ull a[n][m];  // 最终的黑棋的状态，不能够再翻转
        memset(a, 0, sizeof(a));
        function<void(int, int)> bfs = [&](int r, int c) {
            ull tmp = init;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j) cur[i][j] = f[i][j];
            queue<pii> q;
            q.emplace(r, c);
            cur[r][c] = 1; // black
            tmp |= (1ULL << (r * m + c));
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto [xx, yy] : get_edge(x, y)) {
                    q.emplace(xx, yy);
                    cur[xx][yy] = 1;
                    tmp |= (1ULL << (xx * m + yy));
                }
            }
            a[r][c] = tmp;
        };
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) if (f[i][j] == 0) bfs(i, j);
        ull final = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) cur[i][j] = f[i][j];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) 
                if (f[i][j] == 2) {
                    auto p = get_edge(i, j);
                    ull tmp = (init | (1ULL << (i * m + j)));
                    for (auto [x, y] : p) tmp |= a[x][y];
                    if (__builtin_popcountll(final) < __builtin_popcountll(tmp))
                        final = tmp;
                }
        auto print = [&](ull s) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    cout << ((s >> (i * m + j)) & 1ULL) << ' ';
                }
                cout << endl;
            }
        };
        return __builtin_popcountll(final) - __builtin_popcountll(init) - 1;
    }
};