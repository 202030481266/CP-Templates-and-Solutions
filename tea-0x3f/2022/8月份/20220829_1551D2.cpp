#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;

int n, m, k;
int ans[103][103];

bool canSolve() {
    cin >> n >> m >> k;
    if (m / 2 * n < k) return false;
    if (n % 2 == 0) return k % 2 == 0;
    if (m % 2 == 0) {
        int x = m / 2;
        return k >= x && (k - x) % 2 == 0;
    }
    return false;
}

int vis[30];
constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

vector<int> getNeighbors(int x, int y) {
    vector<int> alreadyUse;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dirs[i][0], ny = y + dirs[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && ans[nx][ny]) alreadyUse.push_back(ans[nx][ny]);
    }
    return alreadyUse;
}

int getAvailableChar(int x, int y, int t) {
    int use = 1;
    auto nei1 = getNeighbors(x, y);
    vector<int> nei2;
    if (t == 0) nei2 = getNeighbors(x, y + 1);
    else nei2 = getNeighbors(x + 1, y);
    nei1.reserve(nei1.size() + nei2.size());
    nei1.insert(nei1.end(), nei2.begin(), nei2.end());
    for (int v : nei1) vis[v] = 1;
    for (int i = 1; i <= 26; ++i) {
        if (!vis[i]) {
            use = i;
            break;
        }
    }
    for (int v : nei1) vis[v] = 0; // clear
    return use;
}

void drawRow(int i, int j) {
    ans[i][j] = ans[i][j + 1] = getAvailableChar(i, j, 0);
}

void drawCol(int i, int j) {
    ans[i][j] = ans[i + 1][j] = getAvailableChar(i, j, 1);
}

void constructSolution() {
    memset(ans, 0, sizeof(ans));
    if (n % 2 == 0) {
        // k % 2 == 0
        for (int col = 0; col < m && k > 0; col += 2) {
            for (int row = 0; row < n && k > 0; row += 2) {
                drawRow(row, col);
                drawRow(row + 1, col);
                k -= 2;
            }
        }
    }
    else {
        // m % 2 == 0, k >= m / 2 && (k - m / 2) % 2 == 0
        for (int col = 0; col < m && k > 0; col += 2) {
            drawRow(0, col);
            k -= 1;
        }
        for (int col = 0; col < m && k > 0; col += 2) {
            for (int row = 1; row < n && k > 0; row += 2) { // (n - 1) % 2 == 0
                drawRow(row, col);
                drawRow(row + 1, col);
                k -= 2;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!ans[i][j]) {
                assert(!ans[i + 1][j]);
                drawCol(i, j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << static_cast<char>(ans[i][j] + 'a' - 1);
        }
        cout << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        bool res = canSolve();
        cout << (res ? "YES\n" : "NO\n");
        if (res) constructSolution();
    }
}

