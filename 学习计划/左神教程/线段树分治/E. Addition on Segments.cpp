// https://codeforces.com/problemset/problem/981/E

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 1e4 + 7;
static constexpr int maxb = 20;
static constexpr int maxm = 1e6 + 7;

using bs = bitset<maxn>;

int n, q;
int head[maxn << 2], to[maxm], nxt[maxm], eCount = 0;
struct query { int l, r, val; } queries[maxn]; 

// for dynamic program
bs dp[maxb];
bs ans;

void addEdge(int rt, int qid)
{
	to[eCount] = qid;
	nxt[eCount] = head[rt];
	head[rt] = eCount++;
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid+1, r

void add(int rt, int l, int r, int L, int R, int qid)
{
	if (L <= l && r <= R)
	{
		addEdge(rt, qid);
		return;
	}
	if (R <= mid) add(lson, L, R, qid);
	else if (L > mid) add(rson, L, R, qid);
	else
	{
		add(lson, L, mid, qid);
		add(rson, mid + 1, R, qid);
	}
}

void dfs(int rt, int l, int r, int d)
{
	dp[d] = dp[d - 1];
	for (int i = head[rt]; ~i; i = nxt[i])
	{
		int val = queries[to[i]].val;
		// dp[i][j] |= dp[i][j] | dp[i-1][j] | dp[i-1][j-val]
		dp[d] |= (dp[d] << val);
	}
	if (l == r)
	{
		ans |= dp[d];
	}
	else
	{
		dfs(lson, d + 1);
		dfs(rson, d + 1);
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= q; ++i)
	{
		cin >> queries[i].l >> queries[i].r >> queries[i].val;
		add(1, 1, n, queries[i].l, queries[i].r, i);
	}
	dp[0].set(0);
	dfs(1, 1, n, 1);
	vector<int> result;
	for (int i = 1; i <= n; ++i)
	{
		if (ans.test(i)) result.push_back(i);
	}
	cout << result.size() << '\n';
	for (int i = 0; i < result.size(); ++i)
	{
		if (i == (int)result.size() - 1) cout << result[i] << '\n';
		else cout << result[i] << ' ';
	}
}
