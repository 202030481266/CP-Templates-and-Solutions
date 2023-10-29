class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        // 所有点的的最小边长的多边形
        // 可以证明不会存凹多边形
        // 计算机几何学来说的话： 就是凸包

        // Andrew 算法
        int n = trees.size(), vis[n];
        memset(vis, 0, sizeof(n));
        vector<int> s;

        sort(trees.begin(), trees.end());

        auto f = [&](int a, int b, int c) -> int {
            // vector a->b * b->c , 计算存在顺序
            // cross multiple
            return (trees[c][1] - trees[a][1]) * (trees[b][0] - trees[a][0]) - (trees[c][0] - trees[a][0]) * (trees[b][1] - trees[a][1]);
        };

        // start from the left point
        // use vis to avoid the line 
        s.push_back(0);
        for (int i = 1; i < n; ++i) {
            while (s.size() >= 2 && f(s[s.size() -  2], s[s.size() - 1], i) < 0) {
                vis[s.back()] = 0;
                s.pop_back();
            }
            vis[i] = 1; // 为了防止重复的便利相同的点
            s.push_back(i);
        }
        int m = s.size();
        // 这里必须遍历到左端点的 0， 因此我们在一开始就没有设置vis[0] = 1
        for (int i = n - 1; i >= 0; --i) {
            if (vis[i]) continue;
            while (s.size() > m && f(s[s.size() - 2], s[s.size() - 1], i) < 0) {
                vis[s.back()] = 0;
                s.pop_back();
            }
            vis[i] = 1;
            s.push_back(i);
        }
        vector<vector<int>> ans;
        s.pop_back();
        for (int& i : s) ans.push_back(trees[i]);
        return ans;
    }
};