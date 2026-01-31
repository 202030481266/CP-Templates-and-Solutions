class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int n = satisfaction.size(), ans = 0;
        sort(satisfaction.begin(), satisfaction.end());

        // inequality
        // if the len is k , we should take the last k ones
        int sum = 0, pre = 0;
        for (int i = n - 1; i >= 0; --i) {
            sum += satisfaction[i] + pre;
            pre += satisfaction[i];
            ans = max(ans, sum);
        }
        return ans;
    }
};