#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // 完全对称的图形，实际上非常简单，划分相关块即可
        // (i,j), (n-1-i,j), (i,m-1-j), (n-1-i,m-1-j)
        vector vis(n, vector<bool>(m, false));
        int ans = 0;
        // 1, 2, 4
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j]) continue;
                vector<vector<int>>block{{i,j}, {n-1-i,j}, {i,m-1-j}, {n-1-i,m-1-j}};
                int tot = 0, sum = 0;
                for (auto&p : block) {
                    if (vis[p[0]][p[1]]) continue;
                    vis[p[0]][p[1]] = true;
                    tot += 1;
                    sum += grid[p[0]][p[1]];
                }
                assert(tot == 4 || tot == 2 || tot == 1);
                if (tot == 4)
                    ans += min(sum, tot - sum);
                else if (tot == 2) {
                    arr.push_back(tot-sum);
                }
                else ans += sum;
            }
        }
        // 剩下就是从一堆2中选择偶数个，使得最后的答案最小
        sort(arr.begin(), arr.end());
        vector<int> sum(arr.size()+1, 0);
        for (int i = 0; i < arr.size(); ++i) {
            sum[i+1] = sum[i] + arr[i];
        }
        n = arr.size();
        int res = 2*n-sum[n];
        for (int i = 2; i <= n; i += 2) {
            // [1,i], [i+1,n]
            int cost = (i+1 <= n ? 2*(n-i)-(sum[n]-sum[i]):0);
            res = min(res, sum[i] + cost);
        }
        return ans+res;
    }
};