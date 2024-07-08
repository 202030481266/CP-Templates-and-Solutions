#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1301;
const int MAXS = 2001;

char num[MAXN];
int n;
int tree[MAXS][10];
int fail[MAXS];
int cnt = 0;
bool alert[MAXS];
int dp[MAXN][MAXS][2][2];

void clear() {
    memset(dp, -1, sizeof(dp));
}

void insert(const string& word) {
    int u = 0;
    for (char ch : word) {
        int c = ch - '0';
        if (tree[u][c] == 0) {
            tree[u][c] = ++cnt;
        }
        u = tree[u][c];
    }
    alert[u] = true;
}

void setFail() {
    queue<int> q;
    for (int i = 0; i <= 9; i++) {
        if (tree[0][i] > 0) {
            q.push(tree[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i <= 9; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];
                q.push(tree[u][i]);
            }
        }
        alert[u] |= alert[fail[u]];
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> num;
    n = strlen(num);
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string word;
        cin >> word;
        insert(word);
    }
    setFail();
    clear();
    cout << f1(0, 0, 0, 0) << endl;

    return 0;
}