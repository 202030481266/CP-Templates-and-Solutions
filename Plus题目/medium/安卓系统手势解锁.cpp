#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

int dp[1<<9][9];
class Solution {
public:
    int numberOfPatterns(int m, int n) {
        memset(dp,0,sizeof(dp));
        vector<pii> q;
        for (int i = 0; i < 9; ++i) {
            dp[1<<i][i] = 1;
            q.push_back({1<<i, i});
        }
        int ans = 0;
        for (int d = 1; d <= n && !q.empty(); ++d) {
            vector<pii> nq;
            for(auto [status, ed] : q) {
                int x = ed / 3, y = ed % 3;
                if (d >= m) ans += dp[status][ed];
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if ((status >> (i*3+j)) & 1) continue;
                        int sx = abs(i-x), sy = abs(j-y), mx = max(sx, sy), mn = min(sx, sy);
                        if (mx == 1) {
                            // 1,0, 1,1 
                            int nstatus = status | (1<<(i*3+j));
                            if (dp[nstatus][i*3+j] == 0) nq.push_back({nstatus, i*3+j});
                            dp[nstatus][i*3+j] += dp[status][ed];
                        }
                        else {
                            if (mn == 1) {
                                // 2,1
                                int nstatus = status | (1<<(i*3+j));
                                if (dp[nstatus][i*3+j] == 0) nq.push_back({nstatus, i*3+j});
                                dp[nstatus][i*3+j] += dp[status][ed];
                            }
                            else if (mn == 2) {
                                // 2,2
                                int mid_x=(i+x)/2, mid_y=(j+y)/2, t1=mid_x*3+mid_y;
                                if ((status>>t1)&1) {
                                    int nstatus = status | (1<<(i*3+j));
                                    if (dp[nstatus][i*3+j] == 0) nq.push_back({nstatus, i*3+j});
                                    dp[nstatus][i*3+j] += dp[status][ed];
                                }
                            }
                            else {
                                // 2,0
                                if (sx == 2) {
                                    int mid = (i+x)/2, t1=mid*3+j;
                                    if ((status>>t1)&1) {
                                        int nstatus = status | (1<<(i*3+j));
                                        if (dp[nstatus][i*3+j] == 0) nq.push_back({nstatus, i*3+j});
                                        dp[nstatus][i*3+j] += dp[status][ed];
                                    }
                                }
                                else {
                                    int mid = (j+y)/2, t1=i*3+mid;
                                    if ((status>>t1)&1) {
                                        int nstatus = status | (1<<(i*3+j));
                                        if (dp[nstatus][i*3+j] == 0) nq.push_back({nstatus, i*3+j});
                                        dp[nstatus][i*3+j] += dp[status][ed];
                                    }
                                }
                            }
                        }
                    }
                }
            }
            q = move(nq);
        }
        return ans;
    }
};