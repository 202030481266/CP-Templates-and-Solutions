const int N = 1000010;
int n, m, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];
char s[N];  // index from 1 to n


// 不加优化版本，更好理解，但是常数很大
void SA() {
	scanf("%s", s + 1);
	m = 127;
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];  
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
	memcpy(oldrk + 1, rk + 1, n * sizeof(int));
	for (int i = 1, p = 0; i <= n; ++i) {
		if (oldrk[sa[i]] == oldrk[sa[i - 1]]) rk[sa[i]] = p;
		else rk[sa[i]] = ++p;
	}
	for (int w = 1; w < n; w <<= 1, m = n) { // 对第二关键字排序
		memset(cnt, 0, sizeof(cnt));
		memcpy(id + 1, sa + 1, n * sizeof(int));  // 保存副本
		for (int i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];  // i是排名
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];  
		// 对第一关键字排序
		memset(cnt, 0, sizeof(cnt));
		memcpy(id + 1, sa + 1, n * sizeof(int));
		for (int i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
		memcpy(oldrk + 1, rk + 1, n * sizeof(int));
		for (int p = 0, i = 1; i <= n; ++i) {  
			if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) 
				rk[sa[i]] = p;
			else rk[sa[i]] = ++p;
		}
	}
	for (int i = 1; i <= n; ++i) cout << sa[i] << ' ';
}

int main() {
	SA();
}


// 优化版本，加了内存访问优化，优化了值域
int key1[N]; 
bool cmp (int x, int y, int w) {
	return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}
void SA_Optimize() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	m = 127;
	for (int i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
	int p, i;
	for (int w = 1; w < n; w <<= 1, m = p) {
		for (p = 0, i = n; i > n - w; --i) id[++p] = i; // 没有第二关键字，直接放前面
		for (int i = 1; i <= n; ++i) // 遍历排名，把排名小的放前面
			if (sa[i] > w) id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; ++i) ++cnt[key1[i] = rk[id[i]]];  // rk 就还是上一次排序的rk数组
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i) sa[cnt[key1[i]]--] = id[i];
		memcpy(oldrk + 1, rk + 1, n * sizeof(int));
		for (p = 0, i = 1; i <= n; ++i)
			rk[sa[i]] = (cmp(sa[i], sa[i - 1], w) ? p : ++p);
		if (p == n) {
			for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
			break;  // 排序结束
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
}


// 求解height数组，O(n)
void get_height() {
	SA();
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 0) continue;
		if (k) --k;  // height[rk[i]] >= height[rk[i-1]] - 1
		while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
		height[rk[i]] = k;
	}
}