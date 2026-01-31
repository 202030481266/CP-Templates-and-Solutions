#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

struct Bitset {
    int N;
    vector<ull> arr;
    Bitset(): N(0) {}
    Bitset(int _n):N(_n),arr(((_n-1)/64+1),0) {}
    Bitset& operator ^= (const Bitset& rhs) { // we don't want copy
        for (int i = 0; i < arr.size(); ++i) 
            arr[i] ^= rhs.arr[i];
        return *this;
    }
    int getbit (int v) {
        ull bits = arr[v/64];
        return (bits & (1ull<<(v%64))) ? 1 : 0;
    }
    void setbit (int v) {
        // assert(v==0 || v==1);
        arr[v/64] |= (1ull<<(v%64));
    }
};
int n, m;

// 偶数 + 偶数 = 偶数
// 奇数 + 奇数 = 奇数
// 奇数 + 偶数 = 奇数

void solve() {
    cin >> n >> m;
    vector<Bitset> mat(m, Bitset(n+1)); // m*(n+1), but we now have m rows equations
    string s;
    int tmp;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') mat[i].setbit(j);
        }
        cin >> tmp;
        if (tmp) mat[i].setbit(n);
    }
    // xor gauss
    int ans = n-1; //至少n条方程
    for (int i = 0; i < n; ++i) {
        int mx = 0;
        for (int j = i; j < m; ++j) {
            // 我们不需要寻找上面的，因为一定是主元
            if (mat[j].getbit(i)) {
                if (j > ans) 
                    ans = j; // 最远的一个记录
                swap(mat[i], mat[j]);
                mx = 1;
                break;
            }
        }
        // 开始异或
        if (!mx) {
            cout << "Cannot Determine" << endl;
            return;
        }
        for (int j = 0; j < m; ++j) {
            if (j != i && mat[j].getbit(i)) {
                mat[j] ^= mat[i];
            }
        }
    }
    cout << ans+1 << endl;
    for (int i = 0; i < n; ++i) {
        if (!mat[i].getbit(n)) cout << "Earth" << endl;
        else cout << "?y7M#" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}