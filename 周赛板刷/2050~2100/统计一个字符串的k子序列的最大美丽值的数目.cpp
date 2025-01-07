typedef long long ll;
class Solution {
    int f[26];
public:
    ll pow(ll a, ll b, ll m)
    {
        ll ans = 1;
        a %= m;
        while(b)
        {
            if(b & 1)ans = (ans % m) * (a % m) % m;
            b /= 2;
            a = (a % m) * (a % m) % m;
        }
        ans %= m;
        return ans;
    }
    ll inv(ll x, ll p)//x关于p的逆元，p为素数
    {
        return pow(x, p - 2, p);
    }
    ll C(ll n, ll m, ll p)//组合数C(n, m) % p
    {
        if(m > n)return 0;
        ll up = 1, down = 1;//分子分母;
        for(int i = n - m + 1; i <= n; i++) up = up * i % p;
        for(int i = 1; i <= m; i++) down = down * i % p;
        return up * inv(down, p) % p;
    }
    ll Lucas(ll n, ll m, ll p)
    {
        if(m == 0)return 1;
        return C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
    }
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        for (char& ch : s) ++f[ch - 'a'];
        vector<int> a;
        for (int i = 0; i < 26; ++i)
            if (f[i]) a.push_back(f[i]);
        sort(a.begin(), a.end());
        int n = a.size();
        if (n < k) return 0;
        long long tmp = a[n - k], sum = 0, ans = 1;
        int l = -1, r = n;
        for (int i = n - k; i < n; ++i) {
            if (a[i] != tmp) {
                r = i;
                break;
            }
        }
        for (int i = n - k; i >= 0; --i) {
            if (a[i] != tmp) {
                l = i;
                break;
            }
        }
        ll MOD = 1e9 + 7;
        for (int i = r; i < n; ++i) ans = (ans * a[i]) % MOD;
        int cnt = (r == n ? k : k - (n - r));
        return pow(tmp, cnt, MOD) * C(r - l - 1, cnt, MOD) % MOD * ans % MOD;
    }
};