// 最长公共子串求解问题，L[i, j]=L[i-1, j-1]+1(if x[i]==y[j])

pair<int, int> lcs(string &s, string &t)
{
  if (s.length() == 0 || t.length() == 0) return make_pair(-1, -1);
  int maxStart = 0, maxLength = 0;
  int dp[s.length() + 1][t.length() + 1] = {};
  for (int i = 1; i <= s.length(); i++)
    for (int j = 1; j <= t.length(); j++) {
      if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = 0;
      if (dp[i][j] > maxLength) maxStart = i - dp[i][j], maxLength = dp[i][j];
  }
  return make_pair(maxStart, maxLength);
}