// https://atcoder.jp/contests/abc077/tasks/arc084_b
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

// 巧妙地将问题转换为最短路的问题，同时有利用了倍数的性质转换为同余最短路

int n;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<int> dis(n, inf);

    deque<int> q;
    dis[1] = 1;
    q.emplace_front(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        int x = u*10 % n, y = (u+1) % n;
        if (dis[x] > dis[u]) {
            dis[x] = dis[u];
            q.emplace_front(x);
        }
        if (dis[y] > dis[u] + 1) {
            dis[y] = dis[u] + 1;
            q.emplace_back(y);
        }
    }

    cout << dis[0] << endl;
    return 0;
}