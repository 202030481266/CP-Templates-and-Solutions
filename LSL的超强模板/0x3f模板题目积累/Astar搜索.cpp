/*
	author: xiaoshulin
	Question: https://www.luogu.com.cn/problem/P1379（八数码）
*/

// h(x)可以定义为当前状态下不在应该在的位置上的数字个数
// 速度不如双向搜索

const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int fx, fy;
char ch;

struct matrix {
	int a[5][5];
	bool operator < (matrix x) const {  // 重载运算符因此可以使用set去重
		for (int i = 1; i <= 3; ++i)
			for (int j = 1; j <= 3; ++j)
				if (a[i][j] != x.a[i][j]) return a[i][j] < x.a[i][j];
		return false;
	}
} f, st;

int h(matrix ma) {
	int ret = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			if (ma.a[i][j] != st.a[i][j]) ++ret;
	return ret;
}

struct node {
	matrix a;
	int t;
	bool operator < (node x) const {
		return t + h(a) > x.t + h(x.a);
	}
} x;

priority_queue<node> q;  // 默认创建大根堆
set<matrix> s;

int main() {
	st.a[1][1] = 1;  // 定义标准表
	st.a[1][2] = 2;
	st.a[1][3] = 3;
	st.a[2][1] = 8;
	st.a[2][2] = 0;
	st.a[2][3] = 4;
	st.a[3][1] = 7;
	st.a[3][2] = 6;
	st.a[3][3] = 5;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j) {
			cin >> ch;
			f.a[i][j] = ch - '0';
		}
	q.push(node{f, 0});
	while (!q.empty()) {
		x = q.top();
		q.pop();
		if (!h(x.a)) {
			cout << x.t << '\n';
			return 0;
		}
		for (int i = 1; i <= 3; ++i)
			for (int j = 1; j <= 3; ++j)
				if (!x.a.a[i][j]) fx = i, fy = j;  // 查找0位置的点
		for (int i = 0; i < 4; ++i) {
			int xx = fx + dx[i], yy = fy + dy[i];
			if (1 <= xx && xx <= 3 && 1 <= yy && yy <= 3) {
				swap(x.a.a[fx][fy], x.a.a[xx][yy]);
				if (!s.count(x.a)) {
					s.insert(x.a);
					q.push({x.a, x.t + 1});
				}
				swap(x.a.a[fx][fy], x.a.a[xx][yy]);
			}
		}
	}
	return 0;
}