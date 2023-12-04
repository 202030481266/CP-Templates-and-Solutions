class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();

        int sum = accumulate(cardPoints.begin(), cardPoints.end(),0);;

        vector<int> pre(n + 1), suf(n + 2);
        for (int i = 0; i < n; ++i) {
            pre[i + 1] = pre[i] + cardPoints[i];
        }
        for (int i = n; i >= 1; --i) {
            suf[i] = suf[i + 1] + cardPoints[i - 1];
        }
        int ans = 0;
        for (int i = 0; i <= k; ++i)
            ans = max(ans, pre[i] + suf[n - (k - i) + 1]);
        return ans;
    }
};