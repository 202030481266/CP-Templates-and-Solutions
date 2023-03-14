// 无向无权图，从顶点 1 到其他点的最短路径有多少条

const int maxn = 1e6 + 5;
const int maxm = 2e6 + 5;
const int INF = 2e9;
const int mod = 100003;
int n, m, vis[maxn], dis[maxn], cnt[maxn];
vector<int> G[maxn];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int s = 1;
	queue<int> Q;
	Q.push(s);
	vis[s] = 1;
	cnt[s] = 1;
	dis[s] = 0;
  // BFS
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (!vis[v]) {
				vis[v] = 1;
				dis[v] = dis[u] + 1;
				Q.push(v);
			} if (dis[v] == dis[u] + 1) {
				cnt[v] = (cnt[u] + cnt[v]) % mod;
			}
		}
	}
	for (int i = 1; i <= n; i++) 
		printf("%d\n", cnt[i]);
	return 0;
}