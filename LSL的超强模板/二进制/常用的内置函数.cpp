
// 属于标准库的内置函数


int __builtin_ctz(unsigned int x);
int __builtin_ctzll(unsigned long long x);
// 返回 x 二进制表示下最低位的1后面有多少个0
int __builtin_popcount(unsigned int x);
int __builtin_popcountll(unsigned long long x);
// 返回 x 二进制表示下有多少个1
int  __builtin_clz(int x)
// 返回x的前导0的个数
