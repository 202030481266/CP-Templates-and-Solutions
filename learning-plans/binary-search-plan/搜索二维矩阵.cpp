class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = matrix[0].size();
        int l = 0, r = n; // find the last one that matrix[l][0] <= target
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (matrix[mid][0] <= target) l = mid;
            else r = mid;
        }
        if (matrix[l][0] > target) return false;
        int row = l;
        l = 0, r = m;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (matrix[row][mid] <= target) l = mid;
            else r = mid;
        }
        return matrix[row][l] == target;
    }
};