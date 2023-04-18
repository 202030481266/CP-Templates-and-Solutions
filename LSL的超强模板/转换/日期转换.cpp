// d, m, y 分别是日、月、年 （使用蔡勒公式计算）
// 放回改天是星期几
int whatdays(int d, int m, int y) {
	int ans;
	if (m == 1 || m == 2) m += 12, --y;
	if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3))
		ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
	else ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
	return ans;
}

// 日期相隔天数计算
const int days = 365;
const int s[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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