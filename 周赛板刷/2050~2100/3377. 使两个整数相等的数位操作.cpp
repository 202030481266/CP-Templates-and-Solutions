#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 10000;
int is_prime[maxn], init_prime = 0;
void generate_primes_linear_time(int n) {
    vector<int> lp(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    for (int p : primes) is_prime[p] = 1;
}

int pw[4] = {1, 10, 100, 1000}, dis[maxn];

class Solution {
public:
    int minOperations(int n, int m) {
        if (!init_prime) {
            init_prime = 1;
            generate_primes_linear_time(maxn-1);
        }
        if (is_prime[n] || is_prime[m]) return -1;
        memset(dis, 0x3f, sizeof(dis));
        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.emplace(n, n);
        dis[n] = n;
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (dis[u] != d) continue;
            int v = u;
            for (int i = 0; i < 4 && v; ++i) {
                int r = v%10;
                v /= 10;
                if (r > 0) {
                    // 99 -> 90 + 9
                    int y = u-pw[i];
                    if (!is_prime[y] && dis[y] > d+y) {
                        dis[y]=d+y;
                        q.emplace(dis[y], y);
                    }
                }
                if (r < 9) {
                    int y = u+pw[i];
                    if (!is_prime[y] && dis[y] > d+y) {
                        dis[y]=d+y;
                        q.emplace(dis[y], y);
                    }
                }
            }
        }
        return dis[m] == inf ? -1 : dis[m];
    }
};