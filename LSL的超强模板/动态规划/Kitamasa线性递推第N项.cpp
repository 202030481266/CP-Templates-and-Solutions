// 关键在于理解线性递推的本质是项与项之间的表达式中的系数是不变的
// f(n)=c1*f(n-1)+c2*f(n-2)+...ck*f(n-k) 对于任何一个大于等于k的项都成立
// 那么，f(n)=(c1*c1+c2)*f(n-2)+(c1*c2+c3)*f(n-3)+...c1*ck*f(n-k-1) 对于任何一个大于k的项也都是成立的，而且系数是固定的
// 因此，我们可以认为（数学归纳法），任何k个不同的连续项和任何一个在前面的项其实都有一个固定的系数组合
// 数学表达就是，f(n)=C * F(0)（向量）, 那么 f(n+m)=C * F(m)，C即使固定的系数组合表达，F(0)就是从0开始的k个数字
#include <vector>
using namespace std;

const int mod = 1e9 + 7; // 根据实际需求修改模数

// 快速幂
long long pow(long long a, long long n) {
    long long res = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

// 灵茶山艾府：https://zhuanlan.zhihu.com/p/1964051212304364939

// 给定常系数齐次线性递推式 f(n) = coef[k-1] * f(n-1) + coef[k-2] * f(n-2) + ... + coef[0] * f(n-k)
// 以及初始值 f(i) = a[i] (0 <= i < k)
// 返回 f(n)，其中参数 n 从 0 开始
// 注意 coef 的顺序
// 时间复杂度 O(k^2 log n)，其中 k 是 coef 的长度
int kitamasa(const vector<int>& coef, const vector<int>& a, long long n) {
    int k = coef.size();
    
    // 边界情况
    if (n < (int)a.size()) {
        return ((a[n] % mod) + mod) % mod;
    }
    
    // 特判 k = 0, 1 的情况
    if (k == 0) {
        return 0;
    }
    if (k == 1) {
        return (long long)a[0] * pow(coef[0], n) % mod;
    }
    
    // 已知 f(n) 的各项系数为 a，f(m) 的各项系数为 b
    // 计算并返回 f(n+m) 的各项系数 c
    auto mul = [&](const vector<int>& a, vector<int> b) -> vector<int> {
        vector<int> c(k, 0);
        for (int v : a) {
            for (int j = 0; j < k; j++) {
                c[j] = (c[j] + (long long)v * b[j]) % mod;
            }
            // 原地计算下一组系数，比如已知 f(4) 的各项系数，现在要计算 f(5) 的各项系数
            // 倒序遍历，避免覆盖
            int bk = b[k - 1];
            for (int i = k - 1; i > 0; i--) {
                b[i] = (b[i - 1] + (long long)bk * coef[i]) % mod;
            }
            b[0] = (long long)bk * coef[0] % mod;
        }
        return c;
    };
    
    // 计算 resC，以表出 f(n) = resC[k-1] * a[k-1] + resC[k-2] * a[k-2] + ... + resC[0] * a[0]
    vector<int> resC(k, 0);
    resC[0] = 1;
    vector<int> c(k, 0);
    c[1] = 1;
    
    for (; n > 0; n /= 2) {
        if (n % 2 > 0) {
            resC = mul(c, resC);
        }
        c = mul(c, c); // lambda 按值捕获 c，所以这里直接传 c 即可
    }
    
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + (long long)resC[i] * a[i]) % mod;
    }
    
    return ((ans % mod) + mod) % mod; // 保证结果非负
}