class Solution {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
      // 预处理 power of 10 及其逆元
      vector<int> p10(200), ip10(200);
      auto pow_mod = [&](int a, int b) {
        int ret = 1;
        for (; b; a = (long long)a * a % p, b >>= 1) {
          if (b & 1) ret = (long long)ret * a % p;
        }
        return ret;
      };
      for (int i = 0; i < 200; i++) {
        p10[i] = (i? p10[i-1] * 10LL % p: 1);
        ip10[i] = pow_mod(p10[i], p - 2);
      }
      // 子集 DP 的部分
      int n = gem.size();
      vector<int> len(1 << n);
      vector<unordered_map<int, int> > f(1 << n);
      for (int i = 0; i < n; i++) {
        int x = gem[i];
        do len[1<<i]++;
        while (x /= 10);
        f[1<<i][(p10[len[1<<i]+1]+gem[i]*10LL+9)%p] = 1;
      }
      for (int S = 1; S < (1 << n); S++) {
        int T = S & -S;
        len[S] = len[T] + len[S^T] + 2;
      }
      function<void(int)> dp = [&](int S) {
        if (!f[S].empty()) return;
        for (int T = (S - 1) & S; T; T = (T - 1) & S) {
          dp(T);
          dp(S ^ T);
          for (auto [x, c1]: f[T]) {
            for (auto [y, c2]: f[S^T]) {
              int z = (p10[len[S]-1] + (long long)x * p10[len[S^T]+1] + y * 10LL + 9) % p;
              f[S][z] += c1 * c2;
            }
          }
        }
      };
      // 随手搞掉 p = 2 或 5 的情况
      if (p < 7) {
        dp((1 << n) - 1);
        return f[(1<<n)-1][target];
      }
      // 记忆化搜索部分
      vector<unordered_map<int, int> > g(1 << n);
      function<int(int,int)> dfs = [&](int S, int t) {
        if (g[S].count(t)) return g[S][t];
        if (__builtin_popcount(S) <= 6) {
          // DP 查表
          dp(S);
          return g[S][t] = (f[S].count(t)? f[S][t]: 0);
        }
        int ret = 0;
        for (int T = (S - 1) & S; T; T = (T - 1) & S) {
          if (__builtin_popcount(T) < __builtin_popcount(S ^ T)) {
            // 算左查右
            dp(T);
            for (auto [x, c1]: f[T]) {
              int y = (t - (p10[len[S]-1] + (long long)x * p10[len[S^T]+1] + 9) % p + p) * ip10[1] % p;
              ret += c1 * dfs(S ^ T, y);
            }
          } else {
            // 算右查左
            dp(S ^ T);
            for (auto [y, c2]: f[S^T]) {
              int x = (t - (p10[len[S]-1] + y * 10LL + 9) % p + p) * ip10[len[S^T]+1] % p;
              ret += dfs(T, x) * c2;
            }
          }
        }
        return g[S][t] = ret;
      };
      return dfs((1 << n) - 1, target);
    }
};

