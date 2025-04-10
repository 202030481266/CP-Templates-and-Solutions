#include<bits/stdc++.h>
using namespace std;

const int N = 2e6 + 9, mod = 20100403;

// 模板题目，只要理解了卡特兰数的原理就不难

int f[N], inv[N], finv[N];
void pre()
{
    f[0] = 1;
    for(int i = 1; i < N; i++) f[i] = 1LL * i * f[i - 1] % mod;
    inv[1] = 1;
    for (int i = 2; i < N; i++ )
    {
        inv[i] = (-(1LL * mod / i) * inv[mod % i] ) % mod;
        inv[i] = (inv[i] + mod) % mod;
    }
    finv[0] = 1;
    for(int i = 1; i < N; i++) finv[i] = 1LL * inv[i] * finv[i - 1] % mod;
}
int ncr(int n, int r)
{
    if(n < r || n < 0 || r < 0) return 0;
    return 1LL * f[n] * finv[n - r] % mod * finv[r] % mod;
}
int catalan(int n)
{
    return 1LL * inv[n + 1] * ncr(2 * n, n) % mod;
}


int main() {
	int n, m;
	cin >> n >> m;
	pre();
	cout << (ncr(n+m, n) - ncr(n+m,n+1) + mod) % mod << endl;
}