// https://leetcode.cn/problems/maximum-number-of-visible-points/



class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
    	int n = points.size(), cnt = 0;
    	vector<double> deg;
    	// 计算角度
    	for (auto& point : points) {
    		if (point[0] == location[0] && point[1] == location[1]) { ++cnt; continue; }
    		deg.emplace_back(atan2(point[1] - location[1], point[0] - location[0]));
    	}
    	// 排序 + 转换值域
    	sort(deg.begin(), deg.end());
    	int m = deg.size();
    	for (int i = 0; i < m; ++i) deg.emplace_back(deg[i] + 2 * M_PI);  // 添加元素构造出没有值域冲突的循环数组
    	// 滑动窗口
    	int mx_cnt = 0, l = 0;
    	m *= 2;
    	double degree = angle * M_PI / 180; // 转换为弧度
    	for (int i = 0; i < m; ++i) {
    		while (deg[i] - deg[l] > degree) ++l;
    		mx_cnt = max(mx_cnt, i - l + 1);
    	}
    	return mx_cnt + cnt;
    }
};