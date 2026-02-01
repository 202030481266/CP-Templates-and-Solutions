#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

// 斜率优化   https://www.cnblogs.com/Xing-Ling/p/11210179.html
// 决策单调性 https://www.cnblogs.com/Xing-Ling/p/11317315.html

ll dp[2][1003];
ll sum[1003];
int q[1003];

class Solution {
public:
    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) sum[i + 1] = sum[i] + nums[i];
        // 观察代价函数有决策的单调性
        // w(a,b)=(Sa-Sb)^2+Sa-Sb, w(a,b)+w(a+1,b+1)<=w(a+1,b)+w(a,b+1) -> a<b<c<d, w(a,c)+w(b,d)<=w(a,d)+w(b,c)
        // p<p'<i<i', w(i,p)+w(i',p')<=w(i',p)+w(i,p')
        // dp[p']+w(i,p')<=dp[p]+w(i,p), p in [0, p')
        // dp[p']+w(i,p)+w(i',p')+w(i,p')<=dp[p]+w(i,p)+w(i',p)+w(i,p')
        // dp[p']+w(i',p')<=dp[p]+w(i',p) (conclusion 1)
        // so index p possibly will become a best choice at the future with a segment interval
        // with this conclusion, we can easily get the dp[i'] with maintain a monotonic stack
        // Complexity: O(nlogn)
        auto w = [&](int i, int j) -> ll {
            if (j >= i) return LLINF;
            ll s = sum[i] - sum[j];
            return s * (s + 1); // divide at finally once
        };
        auto solve_1d1d = [&]() -> ll {
            int pre = 0, cur = 1;
            for (int i = 1; i <= n; ++i) dp[pre][i] = LLINF;
            dp[pre][0] = 0;
            for (int t = 1; t <= k; ++t) {
                vector<pii> v; // (start pos, best index)
                v.emplace_back(t - 1, t - 1);
                for (int x = t; x <= n; ++x) {
                    int k = (--lower_bound(v.begin(), v.end(), make_pair(x + 1, 0)))->second;
                    dp[cur][x] = dp[pre][k] + w(x, k);
                    for (int i = (int)v.size() - 1; i >= 0; --i) {
                        int y = v[i].first, oldk = v[i].second; // start from y, oldk is the best
                        if (y > x && dp[pre][oldk] + w(y, oldk) > dp[pre][x] + w(y, x)) v.pop_back();
                        else {
                            // means that oldk still is the best at least at position y
                            int l = y + 1, r = n + 1;
                            while (l < r) {
                                int mid = (l + r) / 2;
                                if (dp[pre][x] + w(mid, x) < dp[pre][oldk] + w(mid, oldk)) r = mid;
                                else l = mid + 1;
                            }
                            if (r != n + 1) v.emplace_back(r, x);
                            break;
                        }
                    }
                    if (v.size() == 0) v.emplace_back(0, x);
                }
                swap(pre, cur);
            }
            return dp[pre][n] / 2;
        };
        // return solve_1d1d();

        // for stage k, we use dp[][k-1] to update dp[][k], let f=dp[][k], g=dp[][k-1]
        // make decision for i, we want to Minimize the f[i]
        // f[i]=Min{g[j]+w(i,j)}, w(i,j)=(Si-Sj)^2+Si-Sj
        // because the function w(i,j) include the item of `SiSj`, so we have to use other tricks
        // if we choose j, then f[i]=g[j]+Si^2+Sj^2-2SiSj+Si-Sj
        // g[j]+Sj^2-Sj=2SiSj+f[i]-Si^2-Si
        // we can treat this equation as a line y=2Si * x+b across a point (Sj,g[j]+Sj^2-Sj) because Si is a constant value in this situation, but j is a variable
        // then we express it as y-(g[j]+Sj^2-Sj)=2Si*(x-Sj), and when x==0, y is the value of f[i]-Si^2-Si
        // we want to minimize the f[i], so we should minimize the y-intercept, different j will bring different line and y-intercept
        // by linear programming, we can get 2 conclusion(Si is increasing strictly):
        //  a. (g[x]+Sx^2-Sx)-(g[j]+Sj^2-Sj)/Sx-Sj <= 2Si get the current better and future better result, the smaller the better (conclusion 2)
        //  b. (g[x]+Sx^2-Sx)-(g[j]+Sj^2-Sj)/Sx-Sj > 2Si get the current worse and future better result, the bigger the worse (conclusion 3)
        // it means we should maintains a lower convex hull, we can use monotonic queue to maintain the best decision point.
        // Complexity: O(n)
        auto get_y = [&](int row, int j) -> ll {
            return dp[row][j] + sum[j] * sum[j] - sum[j];
        };
        auto solve_slope = [&]() -> ll {
            int pre = 0, cur = 1;
            for (int i = 1; i <= n; ++i) dp[pre][i] = LLINF;
            dp[pre][0] = 0;
            int ql = 0, qr = 0; // [ql, qr)
            for (int t = 1; t <= k; ++t) {
                ql = 0;
                qr = 0;
                q[qr++] = t - 1;
                for (int i = t; i <= n; ++i) {
                    ll cur_slope = 2 * sum[i];
                    while (qr - ql >= 2) {
                        ll dy = get_y(pre, q[ql + 1]) - get_y(pre, q[ql]);
                        ll dx = sum[q[ql + 1]] - sum[q[ql]];
                        if ((__int128)dy <= (__int128)cur_slope * dx) ++ql;
                        else break;
                    }
                    dp[cur][i] = dp[pre][q[ql]] + w(i, q[ql]);
                    while (qr - ql >= 2) {
                        int p1 = q[qr - 2];
                        int p2 = q[qr - 1];
                        int p3 = i;
                        ll y2_y1 = get_y(pre, p2) - get_y(pre, p1);
                        ll x2_x1 = sum[p2] - sum[p1];
                        ll y3_y2 = get_y(pre, p3) - get_y(pre, p2);
                        ll x3_x2 = sum[p3] - sum[p2];
                        if ((__int128)x2_x1 * y3_y2 <= (__int128)x3_x2 * y2_y1) --qr;
                        else break;
                    }
                    q[qr++] = i;
                }
                swap(pre, cur);
            }
            return dp[pre][n] / 2;
        };
        return solve_slope();
    }
};
