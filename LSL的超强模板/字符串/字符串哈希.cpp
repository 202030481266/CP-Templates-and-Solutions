// 一般来说使用多项式hash的方法来进行字符串哈希

// 选择进制 B 和模数 M，一般来说进制的数字B要大于字符集的大小即可，而M可以选择一个很大的模数，并且最好是质数
// 对于只有小写字母来说， 27、233、19260817 都是很好的选择


// 防止被卡的方法： 自然溢出，双哈希（基本不可能被卡，但是常数比较大）


// 自然溢出
typedef unsigned long long ull;
ull base=131;
ull a[10010];
char s[10010];
int n,ans=1;
ull hashs(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=ans*base+(ull)s[i];
    return ans&0x7fffffff;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s);
        a[i]=hashs(s);
    }
    sort(a+1,a+n+1);
    for (int i=2;i<=n;i++)
        if (a[i]!=a[i-1])
            ans++;
    printf("%d\n",ans);
}

// 单hash
typedef unsigned long long ull;
ull base=131;
ull a[10010];
char s[10010];
int n,ans=1;
ull mod=19260817;
ull hashs(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=(ans*base+(ull)s[i])%mod;
    return ans;
}
main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s);
        a[i]=hashs(s);
    }
    sort(a+1,a+n+1);
    for (int i=2;i<=n;i++)
        if (a[i]!=a[i-1])
            ans++;
    printf("%d\n",ans);
}


// 双hash，相当于冲突概率相乘极小！
typedef unsigned long long ull;
ull base=131;
struct data
{
    ull x,y;
}a[10010];
char s[10010];
int n,ans=1;
ull mod1=19260817;
ull mod2=19660813;
ull hash1(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=(ans*base+(ull)s[i])%mod1;
    return ans;
}
ull hash2(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=(ans*base+(ull)s[i])%mod2;
    return ans;
}
bool comp(data a,data b)
{
    return a.x<b.x;
}
main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s);
        a[i].x=hash1(s);
        a[i].y=hash2(s);
    }
    sort(a+1,a+n+1,comp);
    for (int i=2;i<=n;i++)
        if (a[i].x!=a[i-1].x || a[i-1].y!=a[i].y)
            ans++;
    printf("%d\n",ans);
}


// 超大质数单hash
typedef unsigned long long ull;
ull base=131;
ull a[10010];
char s[10010];
int n,ans=1;
ull mod=212370440130137957ll;//是质数！！
ull hashs(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=(ans*base+(ull)s[i])%mod;
    return ans;
}
main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s);
        a[i]=hashs(s);
    }
    sort(a+1,a+n+1);
    for (int i=2;i<=n;i++)
        if (a[i]!=a[i-1])
            ans++;
    printf("%d\n",ans);
}