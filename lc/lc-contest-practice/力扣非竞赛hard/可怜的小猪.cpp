typedef unsigned long long ull;
class Solution {
    ull dp[11][11], C[11][11];
    static constexpr int f[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // 根据贪心的原则来说最好就是从一开始就不停止地喂水
        // 并且每一轮喂水都是相互独立的信息

        int epoches = minutesToTest / minutesToDie;

        // 组合数
        for (int i = 0; i <= 10; ++i) C[i][0] = 1;
        for (int i = 1; i <= 10; ++i)
            for (int j = 1; j <= i; ++j)
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];

        // 逆向思维
        // 根据最优决策的原理，我们总可以利用现有的猪的死亡情况决定一个解，并且这些所有的解的都是独立的
        for (int i = 0; i <= 10; ++i) dp[i][1] = f[i];
        for (int i = 2; i <= epoches; ++i) {
            for (int j = 0; j <= 10; ++j) {
                for (int k = 0; k <= j; ++k)
                    dp[j][i] += C[j][k] * dp[k][i - 1];
            }
        }
        for (int i = 0; i <= 10; ++i)
            if (dp[i][epoches] >= buckets) return i;
        return 0;
    }
};