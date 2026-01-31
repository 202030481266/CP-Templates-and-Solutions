// 给定一张 n(n<=20)个点的带权无向图， 点从0~n-1标号，求起点到终点的n-1的最短哈密顿路径
// 哈密顿路径表示从0到n-1经过所有的点恰好一次。

// 状态压缩动态规划
typedef long long ll;
ll f[1 << 20][20];
ll hamilton(int n, int w[20][20]) {
  memset(f, 0x3f, sizeof f);
  f[1][0] = 0;
  for(int i = 1; i < 1 << n; i++) {
    for(int j = 0; j < n; j++)
      if(i >> j & 1) {
        for(int k = 0; k < n; k++) 
          if((i ^ 1 << j) >> k & 1) f[i][j] = min(f[i][j], f[i ^ 1 << j][k] + w[k][j]);
      }
  }
  return f[1 << n - 1][n - 1];
}