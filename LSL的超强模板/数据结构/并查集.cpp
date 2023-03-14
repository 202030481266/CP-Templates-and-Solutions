// 并查集擅长动态维护许多具有传递性的关系

// 常规使用的版本
struct DisjointSet {
  std::vector<int> father, rank;
  DisjointSet(int n): father(n), rank(n) {for(int i=0;i<n;i++) father[i]=i;}
  // 路径压缩
  int find(int v){return father[v]=father[v]==v?v:find(father[v]);}
  // 按秩合并
  void merge(int x,int y) {
    int a=find(x), b=find(y);
    if(rank[a]<rank[b]) father[a]=b;
    else {
      father[b]=a;
      if(rank[b]==rank[a]) ++rank[a];
    }
  }
}

// ”边带权”的并查集
// 在路径压缩的时候进行必要的信息合并更新。

// 维护集合大小的并查集
struct DisjointSet {
  std::vector<int> father, rank, siz;
  DisjointSet(int n): father(n), rank(n), siz(n) {for(int i=0;i<n;i++) father[i]=i, siz[i] = 1;}
  // 路径压缩
  int find(int v){return father[v]=father[v]==v?v:find(father[v]);}
  // 按秩合并
  void merge(int x,int y) {
    int a=find(x), b=find(y);
    if(rank[a]<rank[b]) {
      father[a] = b;
      siz[b] += siz[a];
    }
    else {
      father[b]=a;
      siz[a] = siz[b];
      if(rank[b]==rank[a]) ++rank[a];
    }
  }
}

// 维护到祖宗节点距离的并查集
struct DisjointSet {
  std::vector<int> father, rank, dis;
  DisjointSet(int n): father(n), rank(n), dis(n) {for(int i=0;i<n;i++) father[i]=i;}
  // 路径压缩， 同时合并相关的信息
  int find(int x) {
    if(father[x] != x) {
      int fa = find(father[x]);
      d[x] += d[father[x]];
      // d[x] %= mod; // 当集合划分有固定个数的时候要取模
      father[x] = fa;
    }
    return father[x];
  }
  // 按秩合并
  // 一般来说合并有顺序，所有说这里一般不能按秩合并
  void merge(int x,int y) {
    int a=find(x), b=find(y);
    if(rank[a]<rank[b]) {
      father[a] = b;
      // dis[a] = distance; // distance是dis[a] 的初始化偏移量
    }
    else {
      father[b]=a;
      // dis[b] = distance
      if(rank[b]==rank[a]) ++rank[a];
    }
  }
}

// 扩展域并查集
/* 
  * 把每个节点扩展为两个节点（一正一反），若a与b不能在一起(在同一个集合)，则把a的正节点与b的反节点放一起，把b的正节点与a的反节点放一起，这样就解决了a与b的冲突。
  * 若发现a的正节点与b的正节点已经在一起，那么说明之前的某对关系与(a,b)这对关系冲突，不可能同时满足，即不能成功完成整个操作
*/ 
struct DisjointSet {
  std::vector<int> father;
  DisjointSet(int n): father(2 * n) {for(int i=0;i<2*n;i++) father[i]=i;}
  // 路径压缩
  int find(int v){return father[v]=father[v]==v?v:find(father[v]);}
  // 按秩合并
  void merge(int x,int y) {
    int a=find(x), b=find(y);
    if(rank[a]<rank[b]) father[a]=b;
    else {
      father[b]=a;
      if(rank[b]==rank[a]) ++rank[a];
    }
  }
  void Union(int x, int y) {
    merge(x, y + n); // x merge with the y + n;
    merge(x + n, y); // y merge with the x + n;
  }
};

// 加权并查集
/*
  * N个节点有M对关系(M条边)，每对关系(每条边)都有一个权值w，可以表示距离或划分成多个集合时的集合编号，问题依然是判断是否有冲突或者有多少条边是假的(冲突)等
*/
struct DisjointSet {
  std::vector<int> father, dis;
  DisjointSet(int n): father(n), dis(n) {for(int i=0;i<n;i++) father[i]=i;}
  // 路径压缩
  int find(int v) {
    if(v == father[v]) return v;
    int fa = find(father[v]);
    dis[v] += dis[father[v]];
    // dis[v] %= mod 划分为mod个集合时
    father[v] = fa;
    return father[v];
  }
  // 合并
  void merge(int x, int y, int w) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    father[fx] = fy;
    dis[fx] = dis[y] - dis[x] + w;
    // dis[fx] = (-dis[x] + dis[y] + mod + w) % mod;
  }
};

/*--------------------------------其他的写法-----------------------------*/

//  普通的并查集
const int maxn = 100000;
ll fa[maxn], rank[maxn], n;
void makeSet() {for(int i = 1; i <= n; i++) fa[i] = i, rank[i] = 0;}
int find1(int x) {return x == fa[x] ? x : fa[x] = find1(fa[x]);}
int findset(int x){ //非递归版
  int i,r=x;
  while(r!=fa[r]) r=fa[r];
  while(x!=r){i=fa[x];fa[x]=r;x=i;}
  return r;
}
void unionset(int x,int y){ //按秩合并
  x=findset(x),y=findset(y);
  if(rank[x]>rank[y]) fa[y]=x;
  else{
    fa[x]=y;
    if(rank[x]==rank[y]&&x!=y) 
    rank[y]++;
  } 
}


/*
  * 可以删点修改的并查集
*/
int tmpdfn;
int dfn[Maxn]; //时间戳
int fa[Maxn];
void init(int n){
  for(int i=1;i<=n;i++){
    dfn[i]=fa[i]=i;
  }
  tmpdfn=n;
}
int findset(int x){ //传入时间戳
  return fa[x]==x?x:(fa[x]=findset(fa[x]));
}
void unionset(int x,int y){ //传入时间戳
  fa[findset(x)]=findset(y);
}
void del(int x){ //删除 x 就是更改 x 的时间戳
  dfn[x]=++tmpdfn;
  fa[tmpdfn]=tmpdfn;
}


/* 
  * 重量级数据结构，基于线段树的可持久化并查集：
*/
#define ls tr[k].l,l,mid
#define rs tr[k].r,mid+1,r
struct PUFD {
  int l,r; //左右儿子下标
  int fa; //父亲
  int dep; //深度
  PUFD(int _fa=0){
    l=r=dep=0,fa=_fa;
  }
}tr[Maxn*50];
int rt[Maxn]; //根
int n; //区间范围[1,n]
int sz; //节点总数
void build(int &k,int l,int r){
  k=++sz;
  if(l==r){
    tr[k]=PUFD(l);
    return;
  }
  int mid=l+r>>1;
  build(ls);
  build(rs);
}
//返回以数组下标 k 为根的子树中 pos 的下标
int query(int k,int l,int r,int pos){
  if(l==r) return k;
  int mid=l+r>>1;
  if(pos<=mid) return query(ls,pos);
  return query(rs,pos);
}
//只需复制一份从根(数组下标为 k)到叶子 u 的一条路径
//修改 tr[t].fa=v
void update(int k,int l,int r,int &t,int u,int v){
  t=++sz; //这里复制节点
  if(l==r){ //找到 u,对应新的节点 t
  tr[t]=PUFD(v); //修改父亲指向 v
  //tr[t].dep=tr[k].dep; //继承深度,但并没快多少
    return;
  }
  tr[t].l=tr[k].l,tr[t].r=tr[k].r; //连接好左右儿子
  int mid=l+r>>1;
  if(u<=mid) update(ls,tr[t].l,u,v);
  else update(rs,tr[t].r,u,v);
}
//返回以数组下标 k 为根的子树中 pos 的父亲下标
int findset(int k,int pos){
  int p=query(k,1,n,pos);
  if(tr[p].fa==pos) return p;
  int id=findset(k,tr[p].fa);
  //update(k,1,n,k,tr[p].fa,id); //路径压缩,更慢
  return id;
}
//修改以数组下标 k 为根的子树中 pos 对应的深度
void add(int k,int l,int r,int pos){
  if(l==r){ //找到 pos 对应节点,深度+1
    tr[k].dep++;
    return;
  }
  int mid=l+r>>1;
  if(pos<=mid) add(ls,pos);
  else add(rs,pos);
}
void init(int n){ //初始化第 0 次操作,fa[i]=i
  sz=0;
  build(rt[0],1,n);
}
void unionset(int i,int u,int v){ //第 i 次操作
  rt[i]=rt[i-1];
  int p=findset(rt[i],u),q=findset(rt[i],v);
  if(tr[p].fa==tr[q].fa) return;
  if(tr[p].dep>tr[q].dep) swap(p,q); //p 深度小
  update(rt[i-1],1,n,rt[i],tr[p].fa,tr[q].fa);
  if(tr[p].dep==tr[q].dep) add(rt[i],1,n,tr[q].fa);
}
void print(int k){ //中序遍历
  if(!k) return;
  printf("%d %d %d %d %d\n",k,tr[k].l,tr[k].r,tr[k].fa,tr[k].dep);
  print(tr[k].l);
  print(tr[k].r);
}