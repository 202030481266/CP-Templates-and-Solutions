// https://www.luogu.com.cn/problem/P3402
// 基于随机化启发式合并的可持久化并查集
#include<bits/stdc++.h>
using namespace std;


template<typename T>
struct PersistentArray { // 0 - index
	struct node {
		node* l, * r;
		T x;
	};
	int n = 1;
	vector<node*> root;
	int build(vector<T> v) {
		while (n < v.size()) n <<= 1;
		root.push_back(build(0, n - 1, v));
		return root.size() - 1;
	}
	node* build(int l, int r, vector<T>& v) {
		node* cur = new node();
		if (l == r) {
			if (l < v.size()) cur->x = v[l];
			else cur->x = 0;
		}
		else {
			int mid = (l + r) >> 1;
			cur->l = build(l, mid, v);
			cur->r = build(mid + 1, r, v);
		}
		return cur;
	}
	T get_val(int r, int i) {
		return get_val(root[r], i, 0, n - 1);
	}
	T get_val(node* cur, int i, int l, int r) {
		if (l == r) return cur->x;
		int mid = (l + r) >> 1;
		if (i <= mid) return get_val(cur->l, i, l, mid);
		else return get_val(cur->r, i, mid + 1, r);
	}
	void set(int r, int i, T x) { // 更新一下数组的值
		int k = upd(r, i, x);
		root[r] = root[k];
		root.pop_back();
	}
	// 修改第 i 个元素为 x，返回新的版本
	int upd(int r, int i, T x) {
		root.push_back(upd(root[r], i, x, 0, n - 1));
		return root.size() - 1;
	}
	node* upd(node* pre, int i, T x, int l, int r) {
		node* cur = new node();
		if (l == r) cur->x = x;
		else {
			int mid = (l + r) >> 1;
			if (i <= mid) {
				cur->l = upd(pre->l, i, x, l, mid);
				cur->r = pre->r;
			}
			else {
				cur->r = upd(pre->r, i, x, mid + 1, r);
				cur->l = pre->l;
			}
		}
		return cur;
	}
};
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct PersistentDSU {
	// 依赖于可持久化数组进行构建
	PersistentArray<int> par, sz;
	vector<int> c;
	int cur = 0;
	PersistentDSU() {}
	PersistentDSU(int n, int q) { // q -> 最大的DSU实例个数
		vector<int> p(n + 1);
		for (int i = 1; i <= n; ++i) p[i] = i;
		par.build(p);
		sz.build(vector<int>(n + 1, 1));
		c.resize(q + 1, n);
		cur = 0; // DSU 一开始就是 第 0 个
	}
	int find(int r, int u) {  
		int p = par.get_val(r, u);
		if (p == u) return u;
		int cur = find(r, p);
		par.set(r, u, cur); // 更新父亲的节点，路径压缩
		return cur;
	}
	int merge(int r, int u, int v) { // 返回更新的root
		cur++;
		c[cur] = c[r];
		if ((u = find(r, u)) == (v = find(r, v))) {
			par.upd(r, 0, 0);
			sz.upd(r, 0, 0);
			return cur;
		}
		else c[cur]--;
		if (rnd() % 2) swap(u, v);
		int x = sz.get_val(r, v) + sz.get_val(r, u);
		par.upd(r, u, v);
		sz.upd(r, v, x);
		return cur;
	}
	bool same(int r, int u, int v) {
		return find(r, u) == find(r, v);
	}
	int get_size(int r, int u) {
		return sz.get_val(r, find(r, u));
	}
	int count(int r) { // 连通块数量
		return c[r];
	}
};
int main() {
	int n, m;
	fcin >> n >> m;
	PersistentDSU dsu(n, m + 1);
	vector<int> version(m + 1); // 初始都是 从 第 0 个版本开始
	for (int i = 1; i <= m; ++i) {
		int type, a, b;
		fcin >> type;
		if (type == 1) {
			fcin>> a >> b;
			version[i] = dsu.merge(version[i - 1], a, b);
		}
		else if (type == 2) {
			fcin >> a;
			version[i] = version[a];
		}
		else {
			fcin >>a>>b;
			version[i] = version[i - 1];
			fcout << dsu.same(version[i], a, b) <<endl;
		}
	}
	
}



// 基于启发式合并（深度合并），小的并上大的，可持久化并查集
// 特别提一句，大佬的马蜂真的好看
#include<bits/stdc++.h>
#define N 300005
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,now,to,cnt,rt[N];
struct tree
{
    int ls,rs,fa,dep;
}tr[N*20];
inline int build(int l,int r)
{
    int to=++cnt;
    if(l==r)
    {
        tr[to].fa=l;
        return to;
    }
    int mid=(l+r)>>1;
    tr[to].ls=build(l,mid);
    tr[to].rs=build(mid+1,r);
    return to;
}
inline int que(int now,int l,int r,int x)
{
    if(l==r)return now;
    int mid=(l+r)>>1;
    if(mid>=x)return que(tr[now].ls,l,mid,x);
    else return que(tr[now].rs,mid+1,r,x);
}
inline int find(int now,int a)
{
    int fa=que(rt[now],1,n,a);
    if(tr[fa].fa==a)return fa;
    return find(now,tr[fa].fa);
}
inline int news(int now)
{
    int to=++cnt;
    tr[to]=tr[now];
    return to;
}
inline int hb(int now,int l,int r,int x,int f)
{
    int to=news(now);
    if(l==r)
    {
        tr[to].fa=f;
        return to;
    }
    int mid=(l+r)>>1;
    if(mid>=x)tr[to].ls=hb(tr[now].ls,l,mid,x,f);
    else tr[to].rs=hb(tr[now].rs,mid+1,r,x,f);
    return to;
}
inline int add(int now,int l,int r,int x)
{
    int to=news(now); 
    if(l==r)
    {
        tr[to].dep++;
        return to;
    }
    int mid=(l+r)>>1;
    if(mid>=x)tr[to].ls=add(tr[now].ls,l,mid,x);
    else tr[to].rs=add(tr[now].rs,mid+1,r,x);
    return to;
}
inline void merge(int now,int a,int b)
{
    rt[now]=rt[now-1];
    a=find(now,a);b=find(now,b);
    if(tr[a].fa!=tr[b].fa)
    {
        if(tr[a].dep>tr[b].dep)swap(a,b);
        rt[now]=hb(rt[now-1],1,n,tr[a].fa,tr[b].fa);
        if(tr[a].dep==tr[b].dep)rt[now]=add(rt[now],1,n,tr[b].fa);
    } 
}
inline bool pan(int now,int a,int b)
{
    a=find(now,a),b=find(now,b);
    if(tr[a].fa==tr[b].fa)return 1;
    else return 0;
}
int main()
{
    n=read();m=read();
    rt[0]=build(1,n);
    int op,a,b;
    for(int i=1;i<=m;i++)
    {
        op=read();a=read();
        if(op==1)
        {
            b=read();
            merge(i,a,b);
        }
        if(op==2)rt[i]=rt[a];
        if(op==3)
        {
            b=read();
            if(pan(i-1,a,b))cout<<1<<"\n";
            else cout<<0<<"\n";
            rt[i]=rt[i-1];
        }
    }
    return 0;
}