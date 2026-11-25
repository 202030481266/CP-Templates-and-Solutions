#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    // good[l][r] 表示编号区间 [l, r] 是否要求连通。
    vector<string> good(n + 1, string(n + 1, '0'));

    for (int l = 1; l <= n; ++l) {
        string s;
        cin >> s;

        for (int j = 0; j < static_cast<int>(s.size()); ++j) {
            good[l][l + j] = s[j];
        }
    }

    // 当前每个完整连通块都对应一个连续区间。
    // L[v], R[v] 是顶点 v 所在连通块的左右边界。
    vector<int> L(n + 1), R(n + 1);

    for (int v = 1; v <= n; ++v) {
        L[v] = R[v] = v;
    }

    vector<pair<int, int>> answer;
    answer.reserve(n - 1);

    // 按区间长度从小到大处理。
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            if (good[l][r] != '1' || L[l] == L[r]) {
                continue;
            }

            // 合并的是涉及的完整连通块，
            // 因此合并范围可能超出当前区间 [l, r]。
            int merged_left = L[l];
            int merged_right = R[r];
            int right_block_begin = L[r];

            // 边界使用当前区间的端点 l、r。
            answer.emplace_back(l, r);

            // 中间块取最小编号为代表：
            // 第一个中间块接 r，其余中间块接 l。
            bool first_middle = true;

            for (int p = R[l] + 1;
                 p < right_block_begin;
                 p = R[p] + 1) {

                answer.emplace_back(first_middle ? r : l, p);
                first_middle = false;
            }

            // 必须在遍历完旧连通块后，再统一更新边界。
            for (int v = merged_left; v <= merged_right; ++v) {
                L[v] = merged_left;
                R[v] = merged_right;
            }
        }
    }

    for (const auto& [u, v] : answer) {
        cout << u << ' ' << v << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
