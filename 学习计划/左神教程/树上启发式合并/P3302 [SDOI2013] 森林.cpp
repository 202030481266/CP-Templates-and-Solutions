// 启发式合并 + 可持久化线段树
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N=8e4+10;int n,m,T,cas,last;
int tot,cnt,siz[N],s[N],v[N],root[N];
int top,f[N],lg[N],p[N][35],dep[N],head[N];
struct edge{int to,next;}e[N*4];
struct node{int lc,rc,siz;}tr[N*105];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;	
}
void add(int from,int to){
    e[++cnt].next=head[from];
    e[cnt].to=to;
    head[from]=cnt;
}
void build(int &rt,int pre,int l,int r,int w){
    tr[rt=++top]=tr[pre];tr[rt].siz++;
    if(l==r)return;int mid=(l+r)>>1;
    if(w<=mid)build(tr[rt].lc,tr[pre].lc,l,mid,w);
    else build(tr[rt].rc,tr[pre].rc,mid+1,r,w);
}
void dfs(int u,int fa,int rt){
    build(root[u],root[fa],1,tot,s[u]);
    p[u][0]=fa;dep[u]=dep[fa]+1;
    siz[rt]++;f[u]=rt;
    for(int i=1;i<=18;i++)
        p[u][i]=p[p[u][i-1]][i-1];
    for(int i=head[u];i;i=e[i].next)
        if(e[i].to!=fa)dfs(e[i].to,u,rt);   
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    while(dep[x]>dep[y])
        x=p[x][lg[dep[x]-dep[y]]];
    if(x==y)return x;
    for(int i=lg[dep[x]];i>=0;i--)
        if(p[x][i]!=p[y][i])
            x=p[x][i],y=p[y][i];
    return p[x][0];
}
int query(int i,int j,int fa,int faf,int l,int r,int k){
    if(l==r)return v[l];int mid=(l+r)>>1;
    int sum=tr[tr[i].lc].siz+tr[tr[j].lc].siz
        -tr[tr[fa].lc].siz-tr[tr[faf].lc].siz;
    if(k<=sum)return query(tr[i].lc,tr[j].lc,tr[fa].lc,tr[faf].lc,l,mid,k);
    else return query(tr[i].rc,tr[j].rc,tr[fa].rc,tr[faf].rc,mid+1,r,k-sum);
}
int main(){
    int x,y,k;lg[0]=-1;
    cas=read();n=read();m=read();T=read();
    for(int i=1;i<=n;i++)
        v[i]=s[i]=read(),f[i]=i,lg[i]=lg[i>>1]+1;
    sort(v+1,v+1+n);tot=unique(v+1,v+n+1)-v-1;
    for(int i=1;i<=n;i++)
        s[i]=lower_bound(v+1,v+tot+1,s[i])-v;
    for(int i=1;i<=m;i++)
        x=read(),y=read(),add(x,y),add(y,x);
    char opt[3];
    for(int i=1;i<=n;i++)if(f[i]==i)dfs(i,0,i);
    while(T--){
        scanf("%s",opt);x=read()^last;y=read()^last;
        if(opt[0]=='Q'){
            k=read()^last;
            int anc=lca(x,y),ff=p[anc][0];
            last=query(root[x],root[y],root[anc],root[ff],1,tot,k);
            printf("%d\n",last);
        }else{
            add(x,y);add(y,x);	
            int fx=f[x],fy=f[y];
            if(siz[fx]>siz[fy])dfs(y,x,fx);
            else dfs(x,y,fy);
        }
    }
    return 0;
}