// xiaoshulin
// 2023.12.20

class Solution {
	using vec = pair<int, int>;
public:
	double abs(vec v) {
		return sqrt(v.first * v.first + v.second * v.second);
	}
	double cross(vec v1, vec v2) {
		return v1.first * v2.first + v1.second * v2.second;
	}
	double cos_angle(vec v1, vec v2) {
		return cross(v1, v2) / (abs(v1) * abs(v2));
	}
	vec get_normal_vec(vec v) {
		// left side normal vector
		return vec{-v.second, v.first};
	}
	vec get_vec(int x1, int y1, int x2, int y2) { 
		// (x1, y1) -> (x2, y2)
		return vec{x2 - x1, y2 - y1};
	}
    vector<int> visitOrder(vector<vector<int>>& points, string direction) {
		// 枚举起始的边，似乎思路是找到包围线然后贪心的向前？
		// 已经证明了凸多边形的一种确定解法：贪心
		// 已经找到了凹多边形的一种确定解法：贪心
		// 任意点的扫描贪心解法：
		// 如果下一个旋转方向与下下个方向相同，选择第一个满足条件的点
		// 如果下一个旋转方向与下下个方向不同，选择最后一个满足条件的点
		int n = points.size();

		// start edge should satisfy the most left side points or right side points
		// we should implement a algorithm that can find the leftest side not use point or rightest not use point
		// greedy algorithm
		// we can prove it using the mathematical induction: 
		// If remain points are at the next side of current line, we can construct it!

		// find the leftest point
		int min_x = 0, another = -1;
		for (int i = 1; i < n; ++i) {
			if (points[i][0] < points[min_x][0]) min_x = i, another = -1;
			else if (points[i][0] == points[min_x][0]) another = i;
		}

		vector<int> use(n);

		// caculate the leftest side points and right points
		auto get_side_points = [&](int x1, int y1, int x2, int y2) -> vector<int> {
			vec cur = get_vec(x1, y1, x2, y2); //(x1, y1) -> (x2, y2)
			vec n_cur = get_normal_vec(cur);
			int left_1, left_2, right_1, right_2;
			double l1 = -2, l2 = 2, r1 = -2, r2 = 2;
			for (int i = 0; i < n; ++i) { 
				if (use[i]) continue;
				// [x1, y1] -> points[i]
				vec tmp = get_vec(x2, y2, points[i][0], points[i][1]);
				double c_val = cos_angle(tmp, cur);
				double l_or_r = cos_angle(tmp, n_cur);
				if (l_or_r == 0) {
					// it means this is a valid choice
					if (c_val > l1) left_1 = i, l1 = c_val; 
					if (c_val < l2) left_2 = i, l2 = c_val;
					if (c_val > r1) right_1 = i, r1 = c_val;
					if (c_val < r2) right_2 = i, r2 = c_val;
				}
				else if (l_or_r > 0) {
					// left side
					if (c_val > l1) left_1 = i, l1 = c_val; 
					if (c_val < l2) left_2 = i, l2 = c_val;
				}
				else {
					// right side
					if (c_val > r1) right_1 = i, r1 = c_val;
					if (c_val < r2) right_2 = i, r2 = c_val;
				}
			}
			return vector<int>{left_1, left_2, right_1, right_2};
		};
		
		int cur_x = points[min_x][0], cur_y = (direction[0] == 'L' ? points[min_x][1] - 1 : points[min_x][1] + 1);
		int pre_x = points[min_x][0], pre_y = points[min_x][1], m = direction.size();
		vector<int> p;
		vector<int> ans{min_x};
		use[min_x] = 1;
		if (another != -1 && cur_y == points[another][1]) {
			cur_x = points[another][0], points[another][1];
			use[another] = 1;
			ans.push_back(another);
		}
		else {
			p = get_side_points(pre_x, pre_y, cur_x, cur_y);
			if (direction[0] == 'L') {
				cur_x = points[p[0]][0], cur_y = points[p[0]][1];
				use[p[0]] = 1;
				ans.push_back(p[0]);
			}
			else {
				cur_x = points[p[2]][0], cur_y = points[p[2]][1];
				use[p[2]] = 1;
				ans.push_back(p[2]);
			}
		}
		for (int i = 0; i < m - 1; ++i) {
			bool flag = (direction[i] == direction[i + 1]);
			p = get_side_points(pre_x, pre_y, cur_x, cur_y);
			if (flag) {
				// the direction is the same
				if (direction[i] == 'L') {
					pre_x = cur_x, pre_y = cur_y;
					cur_x = points[p[0]][0], cur_y = points[p[0]][1];
					use[p[0]] = 1;
					ans.push_back(p[0]);
				}
				else {
					pre_x = cur_x, pre_y = cur_y;
					cur_x = points[p[2]][0], cur_y = points[p[2]][1];
					use[p[2]] = 1;
					ans.push_back(p[2]);
				}
			}
			else {
				// the direction is not the same
				if (direction[i] == 'L') {
					pre_x = cur_x, pre_y = cur_y;
					cur_x = points[p[1]][0], cur_y = points[p[1]][1];
					use[p[1]] = 1;
					ans.push_back(p[1]);
				}
				else {
					pre_x = cur_x, pre_y = cur_y;
					cur_x = points[p[3]][0], cur_y = points[p[3]][1];
					use[p[3]] = 1;
					ans.push_back(p[3]);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (!use[i]) {
				ans.push_back(i);
				break;
			}
		}
		return ans;
	}
};
