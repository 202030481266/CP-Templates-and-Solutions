// https://www.spoj.com/problems/WIDGET/

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

const int maxn = 310;
int n, m;

int mat[maxn][maxn];
int inv_table[maxn + 1];

// Function to compute the inverse table
void compute_inv(int p=7) {
    inv_table[1] = 1;
    for (int i = 2; i < p; ++i) {
        // Using the formula inv[i] = p - (inv[p % i] * (p / i)) % p
        inv_table[i] = (int)((p - (long long)inv_table[p % i] * (p / i) % p) % p);
    }
}

int getday(string s) {
    if (s == "MON") return 0;
    else if (s == "TUE") return 1;
    else if (s == "WED") return 2;
    else if (s == "THU") return 3;
    else if (s == "FRI") return 4;
    else if (s == "SAT") return 5;
    else if (s == "SUN") return 6;
    else return -1; // 如果输入无效，返回-1
}

void debug() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= n; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------" << endl;
}

void solve() {
    // cnt day1 day2
    int cnt, day1, day2;
    string s1, s2;
    memset(mat, 0, sizeof(mat));
    int N = max(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> cnt >> s1 >> s2;
        day1 = getday(s1);
        day2 = getday(s2);
        // 这里的 0 -> 1 总共耗时 2 天
        // (day1 + (d-1)) % 7 = day2
        // (day1-1)%7 + d%7 = day2
        // d%7 = (day2-day1+1)%7
        while (cnt--) {
            int tmp;
            cin >> tmp;
            mat[i][tmp-1] = (mat[i][tmp-1] + 1) % 7;
        }
        mat[i][N] = ((day2-day1+1)%7 + 7)%7; // [0,n-1] is variable, n is the value
    }
    // gauss
    // debug();
    for (int i = 0; i < N; ++i) {
        int mx = 0;
        for (int j = 0; j < N; ++j) { 
            if (mat[j][j] > 0 && j < i) continue;
            if (mat[j][i] > 0) {
                mx = mat[j][i];
                swap(mat[j], mat[i]);
                break;
            }  
        }
        if (mx > 0) {
            for (int j = 0; j < N; ++j) { 
                if (j == i || mat[j][i] == 0) continue;
                // Replace gcd with __gcd
				int g = __gcd(mx, mat[j][i]), x = mx / g, y = mat[j][i] / g;
                for (int k = 0; k <= N; ++k) 
                    mat[j][k] = ((mat[j][k] * x - mat[i][k] * y) % 7 + 7) % 7;
            }
        }
        //debug();
    }
    for (int i = 0; i < N; i++) {
        if (mat[i][i] != 0) {
            bool flag = false;
            for (int j = i + 1; j < N; j++) {
                if (mat[i][j] != 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                mat[i][N] = (mat[i][N] * inv_table[mat[i][i]]) % 7;
                mat[i][i] = 1;
            }
        }
    }
    int sign = 1;
    for (int i = 0; i < N; i++) {
        if (mat[i][i] == 0 && mat[i][N] != 0) {
            sign = -1;
            break;
        }
        if (i < n && mat[i][i] == 0) {
            sign = 0;
        }
    }
    if (sign == -1) {
        cout << "Inconsistent data." << '\n';
    } else if (sign == 0) {
        cout << "Multiple solutions." << '\n';
    } else {
        for (int i = 0; i < n; i++) {
            if (mat[i][N] < 3) {
                mat[i][N] += 7;
            }
        }
        for (int i = 0; i < n-1; i++) {
            cout << mat[i][N] << ' ';
        }
        cout << mat[n-1][N] << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    compute_inv();
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        solve();
    }
    return 0;
}