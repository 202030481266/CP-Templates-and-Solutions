// https://www.luogu.com.cn/problem/P3380
//线段树套splay
#include <iostream>
#include <algorithm>
#include <cstdio>
#define mid ((l+r)>>1)
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
using namespace std;
const int maxn=4e6+233;//4*50000
const int inf=0x7fffffff;
int n,m,ans,opt,x,y,z,maxx=-inf,a[maxn];
inline int rd(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9')f=ch=='-'?-1:f,ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct Seg_On_Splay{
    int c[maxn][2],siz[maxn],fa[maxn],cnt[maxn],rt[maxn],v[maxn],SIZE=0;
    inline void pushup(int x){siz[x]=siz[c[x][0]]+siz[c[x][1]]+cnt[x];}
    inline void Clear(int x){fa[x]=c[x][0]=c[x][1]=siz[x]=cnt[x]=v[x]=0;}
    inline int New(int father, int val){
        fa[++SIZE]=father;siz[SIZE]=cnt[SIZE]=1;
        c[SIZE][1]=c[SIZE][0]=0;v[SIZE]=val;
        return SIZE;
    }
    inline void rotate(int x){
        int y=fa[x],z=fa[y],k=c[y][0]==x;
        if(z)c[z][c[z][1]==y]=x;
        fa[x]=z;fa[y]=x;fa[c[x][k]]=y;
        c[y][k^1]=c[x][k];c[x][k]=y;
        pushup(y);pushup(x);
    }
    void splay(int x,int goal){
        while(fa[x]!=goal){
            int y=fa[x],z=fa[y];
            if(z!=goal)(c[y][0]==x^c[z][0]==y)?rotate(x):rotate(y);
            rotate(x);
        }
    }
    inline void sinsert(int pos,int x){
        int root=rt[pos],cur=0;
        if(!rt[pos]){rt[pos]=New(0,x);return;}
        while(true){
            if(v[root]==x){
                cnt[root]++;
                pushup(cur);
                splay(root,0);
                rt[pos]=root;
                return;
            }
            cur=root,root=c[root][v[root]<x];
            if(!root){
                c[cur][v[cur]<x]=New(cur,x);
                pushup(cur);
                splay(SIZE,0);
                rt[pos]=SIZE;
                return;
            }
        }
    }
    inline void find(int pos,int x){
        int root=rt[pos];
        while(true){
            if(v[root]==x){splay(root,0);rt[pos]=root;return;}
            else if(v[root]>x){root=c[root][0];}
            else if(v[root]<x){root=c[root][1];}
        }
    }
    inline int get(int pos,int flag){
        int res=c[rt[pos]][flag];int k=!flag;
        while(c[res][k])res=c[res][k];
        return res;
    }
    inline void del(int pos){
        int root=rt[pos];
        if(cnt[root]>1){cnt[root]--;pushup(root);return;}
        if(!c[root][0]&&!c[root][1]){Clear(rt[pos]);rt[pos]=0;return;}
        if(!c[root][0]||!c[root][1]){
            int p=root;rt[pos]=c[root][0]+c[root][1];
            fa[rt[pos]]=0;Clear(root);return;
        }
        int l=get(pos,0),prert=rt[pos];
        splay(l,0);rt[pos]=l;
        c[rt[pos]][1]=c[prert][1];
        fa[c[prert][1]]=rt[pos];
        Clear(prert);pushup(rt[pos]);
    }
    inline int findrank(int pos,int x){
        int root=rt[pos],ans=0;
        while(true){
            if(!root)return ans;
            if(v[root]==x)return ((c[root][0])?siz[c[root][0]]:0)+ans;
            else if(v[root]<x){
                ans+=((c[root][0])?siz[c[root][0]]:0)+cnt[root];
                root=c[root][1];
            }else if(v[root]>x) root=c[root][0];
        }
    }
    inline int findpre(int pos,int x){
        int root=rt[pos];
        while(root){
            if(v[root]<x){ans=max(ans,v[root]);root=c[root][1];}
            else root=c[root][0];
        }return ans;
    }
    inline int findnext(int pos,int x){
        int root=rt[pos];
        while(root){
            if(v[root]>x){ans=min(ans,v[root]);root=c[root][0];}
            else root=c[root][1];
        }return ans;
    }
    //下面是线段树操作
    void insertSeg(int x,int l,int r,int pos,int val){
        sinsert(x,val);if(l==r)return;
        if(pos<=mid)insertSeg(lson,pos,val);
        else insertSeg(rson,pos,val);
    }
    void askrankSeg(int x,int l,int r,int L,int R,int val){
        if(l>=L&&R>=r){ans+=findrank(x,val);return;}
        if(L<=mid){askrankSeg(lson,L,R,val);}
        if(R>mid){askrankSeg(rson,L,R,val);}
    }
    void changeSeg(int x,int l,int r,int pos,int val){
        find(x,a[pos]);del(x);sinsert(x,val);
        if(l==r)return;
        if(pos<=mid)changeSeg(lson,pos,val);
        else changeSeg(rson,pos,val);
    }
    void askpreSeg(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){ans=max(ans,findpre(x,val));return;}
        if(L<=mid)askpreSeg(lson,L,R,val);
        if(R>mid)askpreSeg(rson,L,R,val);
    }
    void asknextSeg(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){ans=min(ans,findnext(x,val));return;}
        if(L<=mid)asknextSeg(lson,L,R,val);
        if(R>mid)asknextSeg(rson,L,R,val);
    }
}Tree;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        a[i]=rd();
        maxx=max(maxx,a[i]);
        Tree.insertSeg(1,1,n,i,a[i]);
    }
    while(m--){
        opt=rd();
        if(opt==1){
            x=rd();y=rd();z=rd();
            ans=0;Tree.askrankSeg(1,1,n,x,y,z);
            printf("%d\n",ans+1);//rank表示比它小的数加一
        }else if(opt==2){
            x=rd();y=rd();z=rd();
            int l=0,r=maxx+1;
            while(l!=r){
                ans=0;Tree.askrankSeg(1,1,n,x,y,mid);
                if(ans<z)l=mid+1;
                else r=mid;
            }
            printf("%d\n",l-1);
        }else if(opt==3){
            x=rd();y=rd();
            Tree.changeSeg(1,1,n,x,y);
            a[x]=y;maxx=max(maxx,y);
        }else if(opt==4){
            x=rd();y=rd();z=rd();ans=-inf;
            Tree.askpreSeg(1,1,n,x,y,z);
            printf("%d\n",ans);
        }else if(opt==5){
            x=rd();y=rd();z=rd();ans=inf;
            Tree.asknextSeg(1,1,n,x,y,z);
            printf("%d\n",ans);
        }
    }
    return 0;
}