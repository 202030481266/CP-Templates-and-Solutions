const int inf = ~0u >> 1, N = 10010, M = 0x3f3f3f3f;
int s[4][N], p[4]; // 双栈滑窗
int dp[2][N]; // dp
int q[N], st, ed, last; // 单调队列

void pop(vector<int>& nums, int i, int x) {
    if (p[i ^ 1] == 0) {
        p[i ^ 1] = (p[i] + 1) / 2;
        for (int j = 1; j <= p[i ^ 1]; ++j)
            s[i ^ 1][j] = s[i ^ 1][j - 1] & nums[x - p[i] + p[i ^ 1] - j];
        p[i] -= p[i ^ 1];
        for (int j = 1; j <= p[i]; ++j)
            s[i][j] = s[i][j - 1] & nums[x - p[i] + j - 1];
    }
    else --p[i ^ 1];
}
class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), pre = 0, cur = 1;
        memset(dp, 0x3f, sizeof(dp));
        dp[pre][0] = 0;
        for (int& v : andValues) { 
            memset(dp[cur], 0x3f, sizeof(dp[cur])); // 初始化 dp[cur]
            last = 1;
            st = ed = 0;
            q[ed++] = 0; // 提前把0下标装进去，后面要比较
            for (int i = 0; i < 4; ++i)
                s[i][0] = inf, p[i] = 0;
            for (int i = 1; i <= n; ++i) { // 1 index
                for (int j = 1; j < 4; j += 2) {
                    s[j][p[j] + 1] = s[j][p[j]] & nums[i - 1]; 
                    ++p[j];
                }
                while ((s[1][p[1]] & s[0][p[0]]) < v)
                    pop(nums, 1, i);
                while ((s[3][p[3]] & s[2][p[2]]) <= v)
                    pop(nums, 3, i);
                int l = (i - p[1] - p[0] + 1), r = (i - p[2] - p[3] + 1); // [l, r)
                if (r > l && l <= i) {
                    // [l, r)就是求解的对应的区间，但是我们需要的对应的是[l-1,r-1)的dp值
                    while (last < r - 1) {
                        while (st < ed && dp[pre][last] < dp[pre][q[ed - 1]]) --ed;
                        q[ed++] = last++;
                    }
                    while (st < ed && q[st] < l - 1) ++st;
                    dp[cur][i] = (dp[pre][q[st]] == M ? M : dp[pre][q[st]] + nums[i - 1]);
                }
            }
            swap(cur, pre);
        }
        return dp[pre][n] == M ? -1 : dp[pre][n];
    }
};