class Solution {
    typedef long long ll;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        //邻项交换法可以证明的一个事实就是一个工厂对应的维修机器人是连续的一段
        //那么就可以使用DP很容易计算得到最佳的方案
        sort(factory.begin(), factory.end(), [](auto& a, auto& b){
            return a[0] < b[0];
        });
        sort(robot.begin(), robot.end());
        int m = robot.size();
        ll f[m + 1]; 
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        for (auto& fa : factory) {
            for (int j = m; j > 0; --j) {
                ll cost = 0L;
                for (int k = 1; k <= min(j, fa[1]); ++k) {
                    cost += abs(robot[j - k] - fa[0]);
                    f[j] = min(f[j], f[j - k] + cost);
                }
            }
        }
        return f[m];
    }
};