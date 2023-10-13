class Solution {
    const long long num[13] = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600};
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    // 康拖展开
    long long cantorExpansion(const vector<int>& a) {
        long long res = 0;
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            int smaller = 0;
            for (int j = i + 1; j < n; ++j)
                if (a[j] < a[i]) ++smaller;
            res += smaller * num[n - i - 1];
        }
        return res;
    }
    vector<int> reverseCantorExpansion(long long hash, int length) {
        vector<int> permutation;
        vector<int> available(length);

        iota(available.begin(), available.end(), 0);
        for (int i = 0; i < length; ++i) {
            int weight = hash / num[length - i - 1];
            int digit = available[weight];
            permutation.push_back(digit);
            available.erase(available.begin() + weight);
            hash %= num[length - i - 1];
        }

        return permutation;
    }
    int slidingPuzzle(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        vector<int> st;
        vector<int> ed{1, 2, 3, 4, 5, 0};
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                st.push_back(board[i][j]);

        unordered_map<long long, int> dis;
        long long t = cantorExpansion(st), end = cantorExpansion(ed);
        dis[t] = 0;
        queue<int> q;
        q.push(t);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == end) return dis[u];
            vector<int> status = reverseCantorExpansion(u, 6);
            for (int i = 0; i < 6; ++i) {
                if (status[i] == 0) {
                    int x = i / 3, y = i % 3;
                    for (int k = 0; k < 4; ++k) {
                        int nx = x + dirs[k][0], ny = y + dirs[k][1];
                        if (nx >= 0 && nx < 2 && ny >= 0 && ny < 3) {
                            swap(status[nx * 3 + ny], status[i]);
                            long long tmp = cantorExpansion(status);
                            if (!dis.count(tmp)) {
                                dis[tmp] = dis[u] + 1;
                                q.push(tmp);
                            }
                            swap(status[nx * 3 + ny], status[i]);
                        }
                    }
                }
            }
        }
        return -1;
    }
};