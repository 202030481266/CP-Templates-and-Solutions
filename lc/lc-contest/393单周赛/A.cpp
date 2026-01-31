class Solution {
public:
    string findLatestTime(string time) {
        for (int i = 0; i < time.length(); ++i) {
            if (time[i] == '?') {
                // 替换小时
                if (i == 0) {
                    time[i] = (time[1] == '?' || time[1] <= '1') ? '1' : '0';
                } else if (i == 1) {
                    time[i] = (time[0] == '1') ? '1' : '9';
                } else if (i == 3) { // 替换分钟的高位
                    time[i] = '5';
                } else if (i == 4) { // 替换分钟的低位
                    time[i] = '9';
                }
            }
        }
        return time;
    }
};