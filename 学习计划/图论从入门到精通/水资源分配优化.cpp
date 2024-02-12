class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        sort(pipes.begin(), pipes.end(), [&](const vector<int>& a, const vector<int>& b){
            return a[2] < b[2];
        }); 
        int sum = accumulate(wells.begin(), wells.end(), 0);
        vector<int> fa(n);
        iota(fa.begin(), fa.end(), 0);
        function<int(int)> find = [&](int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]);
        };
        int ans = sum, res = sum;
        for (int i = 0; i < pipes.size(); ++i) {
            int x = pipes[i][0] - 1, y = pipes[i][1] - 1;
            if (find(x) == find(y)) continue;
            int fx = find(x), fy = find(y);
            if (wells[fx] < wells[fy]) swap(fx, fy);
            // fx -> fy, wellls[fy] <= wells[fx]
            if (ans > res - wells[fx] + pipes[i][2]) {
                res = res - wells[fx] + pipes[i][2];
                ans = res;
                fa[fx] = fy;
            }
        }
        return ans;
    }
};