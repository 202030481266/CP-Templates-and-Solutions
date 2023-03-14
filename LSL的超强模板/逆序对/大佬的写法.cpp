#include<cstdio>
#include<iostream>
using namespace std;
int n,a[500010],c[500010];
long long ans;

void msort(int b,int e)//归并排序
{
    if(b==e)  
		return;
    int mid=(b+e)/2,i=b,j=mid+1,k=b;
    msort(b,mid),msort(mid+1,e);
    while(i<=mid&&j<=e)
    	if(a[i]<=a[j])
    		c[k++]=a[i++];
    	else
    		c[k++]=a[j++],ans+=mid-i+1;//统计答案
    while(i<=mid)
    	c[k++]=a[i++];
    while(j<=e)
    	c[k++]=a[j++];
    for(int l=b;l<=e;l++)
    	a[l]=c[l];
} 

int main()
{
    scanf("%d",&n); 
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    msort(1,n);
    printf("%lld",ans);
    return 0;
}

/* -------------------------------------树状数组写法----------------------------------- */
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int tree[500010],ranks[500010],n;
long long ans; 
struct point
{
    int num,val;
}a[500010];
inline bool cmp(point q,point w)
{
    if(q.val==w.val)
        return q.num<w.num;
    return q.val<w.val;
}
inline void insert(int p,int d)
{
    for(;p<=n;p+=p&-p)
        tree[p]+=d; 
}
inline int query(int p)
{
    int sum=0;
    for(;p;p-=p&-p)
        sum+=tree[p];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].val),a[i].num=i;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
        ranks[a[i].num]=i;
    for(int i=1;i<=n;i++)
    {
        insert(ranks[i],1);
        ans+=i-query(ranks[i]);
    }
    printf("%lld",ans);
    return 0;
} 

