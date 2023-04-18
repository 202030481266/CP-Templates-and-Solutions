const int days = 365;
const int s[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
class Solution {
public:
    bool isleap(int y) { return (y % 400 == 0 || y % 100 && y % 4 == 0); } // 是否是闰年
    int leap(int y) { return (!y ? 0 : y / 4 - y / 100 + y / 400); }  // 过了多少闰年
    int calc(int day, int month, int year) {  // 转换为公元后多少天
        int res = (year - 1) * days + leap(year - 1);
        for (int i = 1; i < month; ++i) res += s[i];
        if (isleap(year) && month > 2) ++res;
        return res + day;
    }
    int count_day(int da, int ma, int ya, int db, int mb, int yb) {
        return abs(calc(da, ma, ya) - calc(db, mb, yb));
    }
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int ma1 = stoi(arriveAlice.substr(0, 2)), da1 = stoi(arriveAlice.substr(3, 2));
        int ma2 = stoi(leaveAlice.substr(0, 2)), da2 = stoi(leaveAlice.substr(3, 2));
        int mb1 = stoi(arriveBob.substr(0, 2)), db1 = stoi(arriveBob.substr(3, 2));
        int mb2 = stoi(leaveBob.substr(0, 2)), db2 = stoi(leaveBob.substr(3, 2));
        for (int i = 0; i < ma1; ++i) da1 += s[i];
        for (int i = 0; i < ma2; ++i) da2 += s[i];
        for (int i = 0; i < mb1; ++i) db1 += s[i];
        for (int i = 0; i < mb2; ++i) db2 += s[i];
        if (da2 < db1 || db2 < da1) return 0;
        return (da1 <= db1 ? min(db2, da2) - db1 + 1 : min(db2, da2) - da1 + 1);
    }
};