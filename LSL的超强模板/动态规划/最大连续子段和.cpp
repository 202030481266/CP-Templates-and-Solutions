// hdu 1003

int dp[maxn], n;
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> dp[i];
  int l = 1, r = 1, start = 1, maxx = dp[1];
  for(int i = 2; i <= n; i++) {
    if(dp[i - 1] >= 0) dp[i] += dp[i - 1]; 
    else start = i;
    if(dp[i] > maxx) maxx = dp[i], l = start, r = i;
  }
  cout << maxx << ' ' << l << ' ' << r << endl;
}

// 多次询问区间的最大和使用线段树解决