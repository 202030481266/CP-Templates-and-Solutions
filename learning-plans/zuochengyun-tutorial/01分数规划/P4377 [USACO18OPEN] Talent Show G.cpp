#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 255;
int n, W, w[maxn], t[maxn]; 

const int eps = 1e-7;

// 限制规定从k个变换了一个可以影响优化目标的限制
// 所以不能单单使用排序，因为可能存在一个负值对于满足这个限制十分有效，哪怕给优化目标带来了很大负值

bool check(double d) {
    vector<double> a;
    vector<int> b;
    int weight = 0; 
    double cur = 0;
    for (int i = 0; i < n; ++i) {
        double tmp = t[i] - d * w[i];
        if (tmp >= 0) {
            weight += w[i];
            cur += tmp;
        } 
        else {
            a.push_back(tmp);
            b.push_back(w[i]);
        }
    }
    if (weight >= W) return true;
    if (cur == 0) return false;
    int sub = W - weight, N = sub + 1000; 
    vector<double> dp(N+1, -INF);
    /*
        这里有一个重要的dp优化分析，不用过不了
        首先这里全部都是负数，肯定是选择的越少越好，对于一个合法方案，我们可以枚举其中最后一个，这样方案的总重量肯定小于sub
        所以dp的空间值域最多就是 sub + max(b[i])
    */
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = N; j >= b[i]; --j) {
            dp[j] = max(dp[j], dp[j-b[i]] + a[i]);
        }
    }
    for (int i = sub; i <= N; ++i) {
        if (dp[i] + cur >= 0) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> W;

    for (int i = 0; i < n; ++i) cin >> w[i] >> t[i];

    double l = 0, r = 1000;
    for (int iter = 0; iter < 25; iter++)  {
        double mid = (l+r)/2;
        if (check(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    int final_result = floor(1000 * (l + eps));
    cout << final_result << "\n";
}