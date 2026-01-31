class Solution {
public:
    int countTime(string time) {
        int ans = 1;
        for (int i = 0; i < 5; ++i) {
            if (time[i] == '?') {
                if (i == 0) {
                    // 01,11,21  03,13,23, 04,14
                    if (time[i + 1] == '?') {
                        // ?? 00~23
                        ans *= 24;
                        ++i;
                    }
                    else {
                        if (time[i + 1] - '0' <= 3) ans *= 3;
                        else ans *= 2;
                    }
                }
                else if (i == 1) {
                    // 此处一定是 time[0] != '?'
                    if (time[0] - '0' <= 1) ans *= 10;
                    else ans *= 4;  // 20 21 22 23
                }
                else if (i == 3) {
                    if (time[i + 1] == '?') {
                        // ?? 00~59
                        ans *= 60;
                        ++i;
                    }
                    else ans *= 6; // 01 11 21 31 41 51
                }
                else if (i == 4) {
                    // 此处一定是 time[3] != '?'
                    ans *= 10; // 0~9
                }
            }
        }
        return ans;
    }
};