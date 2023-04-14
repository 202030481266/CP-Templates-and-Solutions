// https://leetcode.cn/problems/best-position-for-a-service-centre/
// 震惊，LeetCode真的有随机梯度下降的题目


class Solution {
public:
    double getMinDistSum(vector<vector<int>>& pos) {
    	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    	double eps = 1e-7, step = 1, decay = 0.5, x = 0, y = 0;
    	int n = pos.size();
    	// 计算平均值
    	for (const auto& p : pos) x += p[0], y += p[1];
    	x /= n, y /= n;
    	// 欧几里得距离之和函数计算
    	auto dis = [&](double xx, double yy) -> double {
    		double tmp = 0;
    		for (const auto& p : pos) tmp += hypot(xx - p[0], yy - p[1]);
    		return tmp;
    	};
    	// 指定学习的指标
    	while (step > eps) {
    		bool is_change = false;
    		for (int i = 0; i < 4; ++i) {
    			// 学习步长是自适应调整的
    			double nx = x + step * dirs[i][0], ny = y + step * dirs[i][1]; 
    			if (dis(nx, ny) < dis(x, y)) {
    				x = nx, y = ny;
    				is_change = true;
    				break;
    			}
    		}
    		if (!is_change) step *= decay;
    	}
    	return dis(x, y);
    }
};