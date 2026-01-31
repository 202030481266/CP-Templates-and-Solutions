// xiaoshulin
// 2023.12.19

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
		int n = mat.size(), m = mat[0].size();

		// 最大值的传递性
		int l = 0, r = m - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			int idx = 0;
			for (int i = 1; i < n; ++i)
				if (mat[i][mid] > mat[idx][mid]) idx = i;
			if (l == r) return {idx, mid};
			// check the left side
			if (mid - 1 >= 0 && mat[idx][mid - 1] > mat[idx][mid]) {
				r = mid - 1;
				continue;
			}
			if (mid + 1 < m && mat[idx][mid + 1] > mat[idx][mid]) {
				l = mid + 1;
				continue;
			}
			return {idx, mid};
		}
		return {-1, -1};
    }
};
