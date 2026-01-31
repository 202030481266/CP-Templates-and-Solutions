#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 22;
const int MAX_S = 1 << MAX_N;
const int INF = 1e9;

int dp[2][MAX_S]; 
int c[MAX_N];


struct Segment {
    int l, r;
} segs[MAX_N];
int seg_cnt;

int n, m, k;

void solve() {
    cin >> n >> m >> k;
    
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
        --c[i];
    }

    if (m == 1) {
        cout << 1 << '\n';
        return;
    }

    sort(c, c + k);
    seg_cnt = 0;
    if (k > 0) {
        int start = c[0];
        int prev = c[0];
        for (int i = 1; i < k; ++i) {
            if (c[i] == prev + 1) {
                prev = c[i];
            } else {
                segs[seg_cnt++] = {start, prev};
                start = c[i];
                prev = c[i];
            }
        }
        segs[seg_cnt++] = {start, prev};
    }

    int cur = 1; 
    dp[cur][0] = 1;
    dp[cur][1] = 2;

    for (int i = 2; i <= n; ++i) {
        cur ^= 1;
        int pre = cur ^ 1;
        
        int b = (i & 1) ^ (n & 1); // 0 为 Max 层, 1 为 Min 层
        int size = 1 << i;         // 当前层状态总数

        for (int s = 0; s < size; ++s) {
            int current_val = b ? INF : 0; 

            for (int t = 0; t < seg_cnt; ++t) {
                int L = segs[t].l;
                int R = segs[t].r;

                if (L >= i) continue;
                int current_R = min(R, i - 1);

                // --- 优化1：贪心确定目标位 (Greedy Target) ---
                // Max(b=0) 想要保留1，所以优先移除0。如果区间里有0，绝对不移除1。
                // Min(b=1) 想要保留0，所以优先移除1。如果区间里有1，绝对不移除0。
                
                int target_bit = -1;
                bool has_preferred = false;
                for (int j = L; j <= current_R; ++j) {
                    if (b == 0 && !((s >> j) & 1)) { has_preferred = true; break; } // Max 发现 0
                    if (b == 1 && ((s >> j) & 1))  { has_preferred = true; break; } // Min 发现 1
                }

                if (b == 0) target_bit = has_preferred ? 0 : 1; 
                else        target_bit = has_preferred ? 1 : 0;

                // --- 优化2：去重转移 (Deduplication) ---
                for (int j = L; j <= current_R; ++j) {
                    int bit = (s >> j) & 1;

                    // 只移除我们确定的目标位
                    if (bit != target_bit) continue;

                    // 连续相同位剪枝：
                    // 如果当前位和前一位相同，且前一位也在当前区间[L, R]内，
                    // 那么移除 j 和移除 j-1 得到的状态是一模一样的。
                    if (j > L && ((s >> j) & 1) == ((s >> (j - 1)) & 1)) {
                        continue;
                    }

                    // 计算前一层的状态索引
                    int nxt = ((s >> (j + 1)) << j) | (s & ((1 << j) - 1));
                    
                    if (!b) { // Max
                        if (dp[pre][nxt] > current_val) current_val = dp[pre][nxt];
                    } else { // Min
                        if (dp[pre][nxt] < current_val) current_val = dp[pre][nxt];
                    }
                }
            }
            dp[cur][s] = current_val;
        }
    }

    long long ans = 0;
    int limit = 1 << n;
    for (int i = 0; i < limit; ++i) ans += dp[cur][i];
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; 
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}