class Solution {
    queue<int> q;
    long long sum = 0;
    int m, n;
public:
    void push(int v) {
        q.push(v);
        sum += v;
        while (q.size() > m) {
            int u = q.front();
            sum -= u;
            q.pop();
        }
    }
    bool checkArray(vector<int>& nums, int k) {
        m = k - 1, n = nums.size();
        for (int i = 0; i <= n - k; ++i) {
            if (nums[i] < sum) return false;
            push(nums[i] - sum);
        }
        for (int i = n - k + 1; i < n; ++i) {
            if (nums[i] != sum) return false;
            push(0);
        }
        return true;
    }
};