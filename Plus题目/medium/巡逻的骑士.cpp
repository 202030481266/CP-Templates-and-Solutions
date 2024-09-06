#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

// 骑士可以走的八个方向的偏移量数组
const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};


class Solution {
public:
    vector<vector<int>> ans;
    int status = 0, N, flag = 0, n, m;
    void dfs(int x, int y) {
        if (flag) return;
        if (status == (1<<N)-1) {
            flag = 1;
            return;
        }
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int pos = nx * m + ny;
                if (!(status & (1 << pos))) {
                    status |= (1 << pos);
                    ans.push_back({nx, ny});
                    dfs(nx, ny);
                    if (flag) return;
                    ans.pop_back();
                    status &= ~(1 << pos);
                }
            }
        }
    }
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        swap(n,m);
        N = n * m;
        this->n = n;
        this->m = m;
        status |= (1<<(r*m+c));
        ans.push_back({r,c});
        dfs(r, c);
        vector<vector<int>> res(n, vector<int>(m));
        for (int i = 0; i < N; ++i) {
            res[ans[i][0]][ans[i][1]] = i;
        }
        return res;
    }
};