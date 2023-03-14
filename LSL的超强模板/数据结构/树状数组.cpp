// Tourist的模板
template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;
 
  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};


// 一维树状数组
struct TreeArray {
  int SIZE = 0;
  vector<int> Tree;
  TreeArray() {}
  void init(int n) {
    SIZE=n; Tree=vector<int>(n+1,0);
    for(int i=1;i<=n;i++) {int temp;cin>>temp;add(i,temp);}
  }
  int lowbit(int x) {return x & (-x);}
  void add(int x,int value) {for(int i=x;i<=SIZE;i+=lowbit(i)) Tree[i]+=value;}
  int getSum(int x) {int sum=0;for(int i=x;i;i-=lowbit(i)) sum+=Tree[i]; return sum;}
  int getSum(int x,int y) {return getSum(y)-getSum(x-1);}
};

// 差分树状数组(区间修改和单点查询)
struct BIT {
  int SIZE = 0;
  vector<int> Tree;
  BIT() {}
  void init(int n) {
    SIZE=n; Tree=vector<int>(n+1,0); int first;cin>>first;add(1,first);
    for(int i=2;i<=n;i++) {int temp;cin>>temp;add(i,temp-first);first=temp;}
  }
  int lowbit(int x) {return x & (-x);}
  void add(int x,int value) {for(int i=x;i<=SIZE;i+=lowbit(i)) Tree[i]+=value;}
  void add(int x, int y,int value) {add(x,value); add(y+1,-value);}
  int getSum(int x) {int sum=0;for(int i=x;i;i-=lowbit(i)) sum+=Tree[i]; return sum;}
};

// 区间修改和区间查询
struct BIT {
  int SIZE = 0;
  vector<int> Tree1,Tree2;
  BIT() {}
  void init(int n) {
    SIZE=n; Tree1=vector<int>(n+1,0); Tree2=vector<int>(n+1,0);
    int first;cin>>first;add(1,first);
    for(int i=2;i<=n;i++) {
      int temp;cin>>temp;
      add(i,temp-first);first=temp;
    }
  }
  int lowbit(int x) {return x & (-x);}
  void add(int x,int value) {for(int i=x;i<=SIZE;i+=lowbit(i)) Tree1[i]+=value,Tree2[i]+=(value*x);}
  void add(int x, int y,int value) {add(x,value); add(y+1,-value);}
  int getSum(int x) {int sum=0;for(int i=x;i;i-=lowbit(i)) sum+=((x+1)*Tree1[i]-Tree2[i]); return sum;}
  int getSum(int x,int y) {return getSum(y)-getSum(x-1);}
};


/*--------------------------------------------其他的写法---------------------------------------*/

// 普通的树状数组
typedef long long ll;
ll n,c[manx];
ll lowbit(ll x){return x & (-x);}
ll sum(ll x){ll res=0; while(x>0){res+=c[x];x-=lowbit(x);}; return res;}
void update(ll x,ll w){while(x<=n){c[x]+=w;x+=lowbit(x);}}
// 获得a[x]的值
ll get(ll x){ll res=c[x];for(int i=1;i<(x&(-x));i<<=1)res-=c[x-i]; return res;}
// 获得第k小的数
ll get_kth(ll k){
  ll ans=0,cnt=0;
  for(int i=20;i>=0;i--) {
    ans+=1<<i;
    if(ans>=n||cnt+c[ans]>=k) ans-=1<<i;
    else else cnt+=c[ans];
  } return ans+1;
}

// 二维树状数组
int n;
int c[Maxn][Maxn];
int lowbit(int x){return x&-x; }
void update(int x,int y,int d){
  for(int i=x;i<=n;i+=lowbit(i))
    for(int j=y;j<=n;j+=lowbit(j))c[i][j]+=d; 
}
int ask(int x,int y){
  int res=0;
  for(int i=x;i>0;i-=lowbit(i))
    for(int j=y;j>0;j-=lowbit(j))
      res+=c[i][j];
  return res; 
}

// 二维差分，重量级，基本没用
ll c[4][Maxn][Maxn];
void U(int id,int x,int y,int d){
  for(int i=x;i<=n;i+=i&-i)
    for(int j=y;j<=m;j+=j&-j)
      c[id][i][j]+=d;
}
ll sum(int id,int x,int y){
  ll res=0;
  for(int i=x;i>0;i-=i&-i)
    for(int j=y;j>0;j-=j&-j)
      res+=c[id][i][j];
  return res;
}
//每个数状数组修改 4 个点,总共修改 16 个点
void update(int x1,int y1,int x2,int y2,int d){
  U(0,x1,y1,d);U(0,x1,y2+1,-d); //c[i][j]
  U(0,x2+1,y1,-d);U(0,x2+1,y2+1,d);
  U(1,x1,y1,x1*d);U(1,x1,y2+1,-x1*d); //i*C[i][j]
  U(1,x2+1,y1,-(x2+1)*d);U(1,x2+1,y2+1,(x2+1)*d);
  U(2,x1,y1,y1*d);U(2,x1,y2+1,-(y2+1)*d); //j*C[i][j]
  U(2,x2+1,y1,-y1*d);U(2,x2+1,y2+1,(y2+1)*d);
  U(3,x1,y1,x1*y1*d);U(3,x1,y2+1,-x1*(y2+1)*d); //i*j*C[i][j]
  U(3,x2+1,y1,-(x2+1)*y1*d);U(3,x2+1,y2+1,(x2+1)*(y2+1)*d);
}
ll get(int x,int y){ //(1,1)->(x,y)的子矩阵和
  return (x+1)*(y+1)*sum(0,x,y)-(y+1)*sum(1,x,y)-(x+1)*sum(2,x,y)+sum(3,x,y);
}
ll solve(int x1,int y1,int x2,int y2){ //(x1,y1)->(x2,y2)的子矩阵和
  return get(x2,y2)-get(x1-1,y2)-get(x2,y1-1)+get(x1-1,y1-1);
}


// 支持最值和单点修改的树状数组
ll n, c[maxn], a[maxn];
int lowbit(int x){return x&(-x);}
void init() {
  for(int i=1;i<=n;i++) {
    c[i]=a[i];
    for(int j=1;j<lowbit(i);j<<=1){c[i]=max(c[i], c[i-j]);}
  }
}
ll query(ll l, ll r) {
  ll ans=a[r];
  while(l<=r) {
    if(r-lowbit(r)>=l-1) {ans=max(ans, c[r]);r-=lowbit(r);}
    else ans=max(ans, a[r--]);
  }
  return ans;
}
void update(int x,int d){ //将 a[x]修改为 d
  a[x]=d; //原数组的值修改
  for(int i=x;i<=n;i+=lowbit(i)){ //父亲需要修改
    if(d>=c[i]) {c[i]=d;continue;} //剪枝
    c[i]=a[i]; //自身
    for(int j=1;j<lowbit(i);j<<=1)
      c[i]=max(c[i],c[i-j]); //i-j 为儿子
  }
}