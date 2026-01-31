// 线段树 + 线性基

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 50005;

#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int n, m;
int b[maxn<<2][32];

#include <type_traits>

// Overload for unsigned int
int my_builtin_clz(unsigned int x) {
    if (x == 0) return 32;
    int n = 0;
    if ((x & 0xFFFF0000U) == 0) { n += 16; x <<= 16; }
    if ((x & 0xFF000000U) == 0) { n += 8; x <<= 8; }
    if ((x & 0xF0000000U) == 0) { n += 4; x <<= 4; }
    if ((x & 0xC0000000U) == 0) { n += 2; x <<= 2; }
    if ((x & 0x80000000U) == 0) { n += 1; }
    return n;
}

// Overload for int
int my_builtin_clz(int x) {
    return my_builtin_clz(static_cast<unsigned int>(x));
}

// Overload for unsigned long long
int my_builtin_clz(unsigned long long x) {
    if (x == 0) return 64;
    int n = 0;
    if ((x & 0xFFFFFFFF00000000ULL) == 0) { n += 32; x <<= 32; }
    if ((x & 0xFFFF000000000000ULL) == 0) { n += 16; x <<= 16; }
    if ((x & 0xFF00000000000000ULL) == 0) { n += 8; x <<= 8; }
    if ((x & 0xF000000000000000ULL) == 0) { n += 4; x <<= 4; }
    if ((x & 0xC000000000000000ULL) == 0) { n += 2; x <<= 2; }
    if ((x & 0x8000000000000000ULL) == 0) { n += 1; }
    return n;
}

// Overload for long long
int my_builtin_clz(long long x) {
    return my_builtin_clz(static_cast<unsigned long long>(x));
}
// Function to compute the MSB position
template<typename T>
int compute_msb_pos(T x) {
    using UnsignedT = typename std::make_unsigned<T>::type;
    UnsignedT ux = static_cast<UnsignedT>(x);

    if (ux == 0) return -1; // Undefined for zero

    int total_bits = sizeof(T) * 8;
    int leading_zeros = my_builtin_clz(ux);
    int msb_pos = (total_bits - 1) - leading_zeros;

    return msb_pos;
}
void pushup(int rt) {
    for (int i = 30; i >= 0; --i) {
        b[rt][i] = b[ls][i]; // from left to right
    }
    for (int i = 30; i >= 0; --i) {
        if (b[rs][i]) {
            int tmp = b[rs][i];
            for (int j = 30; j >= 0 && tmp; --j) {
                if (tmp & (1<<j)) {
                    if (b[rt][j]) tmp ^= b[rt][j];
                    else {
                        b[rt][j] = tmp;
                        break;
                    }
                }
            }
        }
    }
}
void update(int rt, int l, int r, int p, int val) {
    if (l == r) {
        if (val) {
            int hb = compute_msb_pos(val);
            for (int i = hb; i >= 0 && val; --i) {
                if (val & (1<<i)) {
                    if (b[rt][i]) val ^= b[rt][i];
                    else {
                        b[rt][i] = val;
                        break;
                    }
                }
            }
        }
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    pushup(rt);
}
int res[32];
void query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        for (int i = 30; i >= 0; --i) {
            if (b[rt][i]) {
                int tmp = b[rt][i];
                for (int j = 30; j >= 0 && tmp; --j) {
                	if (tmp & (1<<j)) {
	                    if (res[j]) tmp ^= res[j];
	                    else {
	                        res[j] = tmp;
	                        break;
	                    }
	                }
                }
            }
        }
        return;
    }
    if (R <= mid) query(lson, L, R);
    else if (L > mid) query(rson, L, R);
    else {
        query(lson, L, mid);
        query(rson, mid+1, R);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    int op, k, x, L, R, ans;
    for (int i = 0; i < n; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> k >> x;
            update(1, 1, m, k, x);
        }
        else {
            cin >> L >> R;
            memset(res, 0, sizeof(res));
            query(1, 1, m, L, R);
            ans = 0;
            for (int j = 30; j >= 0; --j) ans = max(ans, ans ^ res[j]);
            cout << ans << '\n';
        }
    }    
}