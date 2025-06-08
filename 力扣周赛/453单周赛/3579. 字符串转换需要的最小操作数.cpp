// https://leetcode.cn/problems/minimum-steps-to-convert-string-with-operations/
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 101;

int dp[maxn];
int cnt[26][26][2];
int cost[maxn][maxn][2];

class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        memset(dp, 0x3f, sizeof(dp));
        // 这个cost可以增量计算，因为都是可以在线的，但是这里n非常小，所以直接算
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                cost[i][j][0] = cost[i][j][1] = 0;
                memset(cnt, 0, sizeof(cnt));
                for (int k = i, x = j; k <= j; ++k, --x) {
                    if (word1[k] != word2[k]) ++cnt[word1[k]-'a'][word2[k]-'a'][0];
                    if (word1[k] != word2[x]) ++cnt[word1[k]-'a'][word2[x]-'a'][1];
                }
                for (int k = i, x = j, a, b; k <= j; ++k, --x) {
                    if (word1[k] != word2[k]) {
                        a = word1[k] - 'a';
                        b = word2[k] - 'a';
                        cost[i][j][0] += cnt[a][b][0] + cnt[b][a][0] - min(cnt[a][b][0], cnt[b][a][0]);
                        cnt[a][b][0] = cnt[b][a][0] = 0;
                    }
                    if (word1[k]!= word2[x]) {
                        a = word1[k] - 'a';
                        b = word2[x] - 'a';
                        cost[i][j][1] += cnt[a][b][1] + cnt[b][a][1] - min(cnt[a][b][1], cnt[b][a][1]);
                        cnt[a][b][1] = cnt[b][a][1] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                if (j == 0) dp[i] = min(dp[i], min(cost[j][i][0], cost[j][i][1] + 1));
                else dp[i] = min(dp[i], dp[j-1] + min(cost[j][i][0], cost[j][i][1] + 1));
            }
        }
        return dp[n-1];
    }
};