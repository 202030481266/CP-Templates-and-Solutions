inline int read()//快读
{
    int x=0,f=0;
    char ch=getchar();
    while(ch>'9'||ch<'0'){f|=(ch=='-');ch=getchar();}
    while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return f?-x:x;
}


inline void write(int x) // 快写
{
    char f[200];
    int cnt=0,tmp=x>0?x:-x;
    if(x<0)putchar('-');
    while(tmp>0)f[cnt++]=tmp%10+'0',tmp/=10;
    while(cnt>0)putchar(f[--cnt]);
}

