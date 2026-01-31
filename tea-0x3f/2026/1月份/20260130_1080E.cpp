#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

char s[260][260];
int status[260][260];
ull h[260][260];
ull row_hash[260];
bool can[260];

ull base[26]; // 多重集hash

void bruteforce() {
    int n, m;
    if (!(cin >> n >> m)) return;

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < 26; ++i) {
        base[i] = rng();
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int char_idx = s[i][j] - 'a';
            status[i][j] = status[i][j - 1] ^ (1 << char_idx);
            h[i][j] = h[i][j - 1] + base[char_idx];
        }
    }

    long long ans = 0;
    
    // Manacher 辅助数组，放在外面避免反复开栈
    static int mp[600];

    for (int l = 1; l <= m; ++l) {
        for (int r = l; r <= m; ++r) {
            // 3. O(N) 预处理当前列区间的行信息
            for (int i = 1; i <= n; ++i) {
                int seg = status[i][r] ^ status[i][l - 1];
                // 检查二进制中1的个数，GCC内置函数，比手写快
                can[i] = (__builtin_popcount(seg) <= 1);
                
                // 计算当前行在 [l, r] 的哈希值，O(1) 替代了原来的 26 次循环
                if (can[i]) {
                    row_hash[i] = h[i][r] - h[i][l - 1];
                } else {
                    row_hash[i] = 0; // 其实如果不can，hash值是多少都不重要，因为 Manacher 会跳过
                }
            }

            int len = 2 * n + 1;
            int c = 0, r_boundary = 0;
            for(int k = 0; k < len; k++) mp[k] = 0;
            
            long long current_ans = 0;

            for (int i = 0; i < len; ++i) {
                if ((i & 1) && !can[i / 2 + 1]) {
                    mp[i] = 0;
                    continue;
                }

                int k = (i < r_boundary) ? min(mp[2 * c - i], r_boundary - i) : 1;

                while (i - k >= 0 && i + k < len) {
                    int u = i - k;
                    int v = i + k;
                    
                    bool equal = false;
                    if ((u & 1) == 0) {
                        equal = true; // 分隔符
                    } else {
                        int row_u = u / 2 + 1;
                        int row_v = v / 2 + 1;
                        
                        if (can[row_u] && can[row_v] && row_hash[row_u] == row_hash[row_v]) {
                            equal = true;
                        }
                    }

                    if (equal) k++;
                    else break;
                }

                mp[i] = k;
                if (i + k > r_boundary) {
                    r_boundary = i + k;
                    c = i;
                }
                current_ans += mp[i] / 2;
            }
            ans += current_ans;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bruteforce();
    return 0;
}
