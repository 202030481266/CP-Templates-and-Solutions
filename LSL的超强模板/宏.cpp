using namespace std;
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>          //字符串类
#include <iostream>        //基本输入输出流
#include <iomanip>
#include <sstream>         //基于字符串的流
#include <stdexcept>　　　  //标准异常类
#include <algorithm>       //通用算法
#include <cmath>           //数学运算
#include <numeric>
#include <functional>　　　 //定义运算函数（代替运算符）
#include <complex>　　　　  //复数类
#include <list>　　　　　　 //线性列表容器
#include <vector>          //动态数组容器
#include <stack>　　　　　  //堆栈容器
#include <queue>　　　　　  //队列容器
#include <deque>           //双端队列容器
#include <bitset>          //比特集合
#include <set>　　　　　　  //集合容器
#include <map>　　　　　　  //映射容器
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <ctime>
#define ll long long
#define FOR(i,n) for(int (i)=0;(i)<(n);++(i))
#define PRE(i, m, n, in) for(int (i)=(m);(i)<(n);i+=in)
#define forn(i,n) for(int (i)=0;(i)<(n);++(i))
#define for1(i,n) for(int(i)=1;i<=int(n);++i)
#define fore(i,l,r) for(int(i)=l;i<=int(r);++i)
#define srt(v) sort(v.begin(),v.end())
#define rep(i,n) for(int (i)=(n-1);(i)>=0;--(i))
#define debug(x) cout<<#x" = "<<(x)<<endl
#define printa(a,L,R) for(int i=L;i<R;i++) cout<<a[i]<<(i==R-1?"\n":" ")
#define printv(a) printa(a,0,a.size())
#define print2d(a,r,c) for(int i=0;i<r;i++) for(int j=0;j<c;j++) cout<<a[i][j]<<(j==c-1?"\n":" ")

typedef vector<string>vs;
typedef pair<ll,ll> ii;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<ii> vii;
typedef map<ll,ll> ml;
typedef map<ll, string>mpls;