// https://leetcode.cn/problems/maximal-rectangle/description/
// 本质和柱状图的最大矩形是一样的


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
      heights.push_back(0);
      heights.insert(heights.begin(), 0);
      int ans = 0, n = heights.size();
      stack<int> st; st.push(0);
      for(int i = 1; i < n; i++) {
        while(!st.empty() && heights[i] < heights[st.top()]) {
          int temp = st.top(); st.pop();
          int width = (i - 1) - (st.top() + 1) + 1;
          ans = max(ans, width * heights[temp]);
        }
        st.push(i);
      }
      return ans;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
      int n = matrix.size(), m = matrix[0].size();
      vector<vector<int>> a(n, vector<int>(m, 0));
      vector<vector<int>> height(n, vector<int>(m, 0));
      vector<int> use;
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
          a[i][j] = matrix[i][j] - '0';
        }
      }
      int ans = 0;
      if(n == 0) return ans;
      for(int i = 0; i < m; i++) height[0][i] = a[0][i];
      use = height[0];
      ans = max(ans, largestRectangleArea(use));
      for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
          height[i][j] = (a[i][j]) ? (height[i - 1][j] + 1) : 0;
        }
        use = height[i];
        ans = max(ans, largestRectangleArea(use));
      }
      return ans;
    }
};