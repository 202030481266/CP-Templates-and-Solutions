typedef long long ll;


ll a[100010];
int p;
ll pow_mod(ll x, ll y, int p) { // 快速幂 x^y%p
	ll ans = 1;
	x %= p;
	for (ll i = y; i; i >>= 1, x = x * x % p) 
		if (i & 1) ans = ans * x % p;
	return ans;
}
ll C(ll n, ll m) { // 使用费曼小定理求解组合数逆元
	if (m > n) return 0;
	return ((a[n] * pow_mod(a[m], p - 2, p)) % p * pow_mod(a[n - m], p - 2, p) % p);
}
ll Lucas(ll n, ll m) {
	if (!m) return 1;
	return C(n % p, m % p) * Lucas(n / p, m / p) % p;
}
void init() {
	a[0] = 1;
	for (int i = 1; i <= p; ++i) a[i] = (a[i - 1] * i) % p;
}