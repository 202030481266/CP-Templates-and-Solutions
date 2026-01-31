#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int cnt[2000010];

class Solution {
public:
    long long maxArea(int h, vector<int>& p, string d) {
        int n = p.size();
        // 绝大部分就是二分就可以了（就是最后一个过不了）,但是不严谨，其实存在两个峰的函数
        // [0,2*h-1]
        int k = 0;
        ll res = accumulate(all(p), 0ll), ans = res;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            if (d[i] == 'U') {
                ++k;
                cnt[h - p[i]] -= 2; // 这个时候方向的斜率变化了, U -> D, 1 -> -1
                cnt[2*h - p[i]] += 2; // 这个时候方向的斜率变化了, D -> U, -1 -> 1
            }
            else {
                --k;
                cnt[p[i]] += 2; // 这个时候方向的斜率变化了, D -> U, -1 -> 1
                cnt[h + p[i]] -= 2; // 这个时候方向的斜率变化了, U -> D, 1 -> -1
            }
        }
        // 完全遍历两倍的height空间即可，其实很简单，被数学思维带偏了
        for (int i = 1; i <= 2*h; ++i) {
            res += k;
            if (res > ans) ans = res;
            k += cnt[i];
        }
        return ans;
    }
};