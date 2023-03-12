class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        int n = tasks.size();
        sort(tasks.begin(), tasks.end(), [&](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });
        vector<bool> use(2001);
        vector<int> a[n];
        for (int i = 0; i < n; ++i) {
            int k = 0;
            for (int j = tasks[i][1]; j >= tasks[i][0]; --j) {
                if (use[j]) ++k;
            }
            if (k >= tasks[i][2]) continue;
            for (int j = tasks[i][1]; j >= tasks[i][0] && k < tasks[i][2]; --j) {
                if (!use[j]) {
                    use[j] = true;
                    ++k;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= 2000; ++i)
            if (use[i])
                ++ans;
            
        return ans;
    }
};