#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int dep[55];
int flag;

void init() {
    for (int i = 2; i <= 50; ++i) {
        uint j = i;
        while (j != 1u) {
            ++dep[i];
            j = popcount(j);
        }
    }
}

long long dp[65][65];
string s;

long long dfs(int pos, int count, bool limit) {
    if (pos == s.size()) {
        return count;
    }
    if (!limit && dp[pos][count] != -1) {
        return dp[pos][count];
    }

    long long ans = 0;
    int up = limit ? s[pos] - '0' : 1;

    for (int i = 0; i <= up; ++i) {
        if (count + i > 64) continue;
        ans += dfs(pos + 1, count + i, limit && (i == up));
    }

    if (!limit) {
        dp[pos][count] = ans;
    }
    return ans;
}

long long solve(long long n, int x) {
    s = "";
    while (n > 0) {
        s += to_string(n % 2);
        n /= 2;
    }
    reverse(s.begin(), s.end());

    for (int i = 0; i < 65; ++i) {
        for (int j = 0; j < 65; ++j) {
            dp[i][j] = -1;
        }
    }

    auto get_count = [&](int target_ones) {
        if (target_ones < 0) return 0LL;
        auto dfs_wrapper = [&](auto self, int pos, int current_ones, bool is_limit) -> long long {
            if (current_ones > target_ones) return 0;
            if (pos == s.size()) {
                return current_ones == target_ones;
            }
            if (!is_limit && dp[pos][current_ones] != -1) {
                return dp[pos][current_ones];
            }

            long long res = 0;
            int upper_bound = is_limit ? s[pos] - '0' : 1;

            for (int i = 0; i <= upper_bound; ++i) {
                res += self(self, pos + 1, current_ones + i, is_limit && (i == upper_bound));
            }

            if (!is_limit) {
                dp[pos][current_ones] = res;
            }
            return res;
        };
        
        for (int i = 0; i <= s.size(); ++i) {
            for (int j = 0; j <= target_ones; ++j) {
                dp[i][j] = -1;
            }
        }
        return dfs_wrapper(dfs_wrapper, 0, 0, true);
    };

    return get_count(x);
}

class Solution {
public:
    long long popcountDepth(long long n, int k) {
        if (!flag) {
            flag = 1;
            init();
        }
        if (k == 0) return 1;
        ll ans = 0;
        for (int i = 1; i <= 50; ++i) {
            if (dep[i] + 1 == k) {
                // 有 i 个 1，但是不超过 n 的数字的个数
                ans += solve(n, i);
                if (i == 1) --ans;
            }
        }
        return ans;
    }
};