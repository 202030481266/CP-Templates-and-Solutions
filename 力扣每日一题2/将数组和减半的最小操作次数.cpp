typedef long long ll;
class Solution {
public:
    int halveArray(vector<int>& nums) {
        priority_queue<double> q; 
        double sum = accumulate(nums.begin(), nums.end(), 0.0);
        double res = 0;
        int ans = 0;
        for (int& c : nums) q.push(c * 1.0);
        while (res < sum / 2) {
            double mx = q.top();
            q.pop();
            res += (mx / 2);
            q.push(mx / 2);
            ++ans;
        }
        return ans;
    }
};