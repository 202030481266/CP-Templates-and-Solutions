class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<bool> dp(n, false);
        vector<int> q(n + 1);

        dp[0] = true;
        int p = 1, st = 0, ed = 0;
        q[ed++] = 0;
        for (int i = minJump; i < n; ++i)
            if (s[i] == '0') {
                // 区间 [max(0, i-maxJump), i-minJump]
                // 滑动窗口
                while (p <= i - minJump) {
                    if (dp[p]) {
                        q[ed++] = p;
                    }
                    ++p;
                }
                while (st < ed && q[st] < max(0, i-maxJump)) 
                    ++st;
                dp[i] = (st == ed ? false : true);
            }
        return dp[n - 1];
    }
};