class Solution {
public:
    int countCollisions(string s) {
        int n = s.size();
        int pre = -1, cnt = 0;

        // R 0 L 1 S 2
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'L') {
                if (pre == 0) {
                    ans += 2 + (cnt - 1);
                    pre = 2;
                    cnt = 0;
                }
                else if (pre == 2) ans += 1, pre = 2; // S L -> S
            }
            else if (s[i] == 'R') {
                pre = 0;
                ++cnt;
            }
            else {
                ans += cnt;
                cnt = 0;
                pre = 2;
            }
        }
        return ans;
    }
};