#include<bits/stdc++.h> // 包含常用的C++标准库头文件，bits/stdc++.h是GNU GCC特有的，方便竞赛使用
using namespace std; // 使用标准命名空间

const int N = 3e5 + 9; // 定义一个常量N，通常用于数组大小等，这里虽然定义了但在此代码段中未直接使用

// FFT其实并不难，手推一下蝶形网络就很简单了，参考oi-wiki：https://oi-wiki.org/math/poly/fft/
// 这里的逆变换非常简单，只需要将正变换的根 w = w ^ -1 计算，最后除以n即可

const double PI = acos(-1); // 定义常量PI，值为π，通过反余弦函数acos(-1)计算得到

// 定义复数结构体 (base)
struct base
{
    double a, b; // a: 实部 (real part), b: 虚部 (imaginary part)

    // 构造函数，默认构造一个0+0i的复数
    base(double a = 0, double b = 0) : a(a), b(b) {}

    // 重载加法运算符 (+) 用于复数相加
    // (x1 + i*y1) + (x2 + i*y2) = (x1+x2) + i*(y1+y2)
    const base operator + (const base &c) const
    {
        return base(a + c.a, b + c.b);
    }

    // 重载减法运算符 (-) 用于复数相减
    // (x1 + i*y1) - (x2 + i*y2) = (x1-x2) + i*(y1-y2)
    const base operator - (const base &c) const
    {
        return base(a - c.a, b - c.b);
    }

    // 重载乘法运算符 (*) 用于复数相乘
    // (x1 + i*y1) * (x2 + i*y2) = (x1*x2 - y1*y2) + i*(x1*y2 + y1*x2)
    const base operator * (const base &c) const
    {
        return base(a * c.a - b * c.b, a * c.b + b * c.a);
    }
};

// 快速傅里叶变换 (FFT) 函数
// p: 输入的复数向量，表示多项式的系数（正向FFT）或点值（逆向FFT）
// inv:布尔标志，为true时执行逆傅里叶变换 (IFFT)，为false时执行正向傅里叶变换 (FFT)
void fft(vector<base> &p, bool inv = 0)
{
    int n = p.size(); // 获取向量大小，FFT要求n为2的幂
    int i = 0; // 用于位反转置换的辅助变量

    // 1. 位反转置换 (Bit-Reversal Permutation)
    // 使得p[j]的元素被放到其二进制表示反转后的位置i上
    // 这是为了让后续的蝶形运算能够原址进行 (in-place)
    // 例如，如果n=8, j=1 (001), i会变成4 (100)
    // j=3 (011), i会变成6 (110)
    for(int j = 1; j < n - 1; ++j) // 遍历除第一个和最后一个元素外的所有元素
    {
        // 计算j的位反转后的索引i
        // k从n/2开始，每次右移一位 (k >>= 1)
        // (i ^= k) 表示如果j的当前位为1 (通过k > (i^=k)隐式判断)，则i的对应位也设为1
        // 这是一个巧妙的计算位反转索引的方法，本质上是模拟进位加法
        for(int k = n >> 1; k > (i ^= k); k >>= 1); // 每一次都利用前面的计算结果进行计算，手动写一下很简单
        if(j < i) swap(p[i], p[j]); // 如果j小于其位反转索引i，则交换它们，避免重复交换
    }

    // 2. 蝶形运算 (Butterfly Operations) - Cooley-Tukey算法的迭代实现
    // l: 当前子DFT的长度的一半 (half-length of the sub-DFTs being combined)
    // m: 当前子DFT的完整长度 (m = 2*l)
    for(int l = 1, m; (m = l << 1) <= n; l <<= 1) // l从1开始，每次翻倍，直到m > n
    {
        // ang: 当前m次单位根的角度 (2*PI / m)
        double ang = 2 * PI / m;
        // wn: m次单位根 w_m = e^(i * ang) (对于FFT) 或 e^(-i * ang) (对于IFFT)
        // 如果是IFFT (inv=true)，虚部符号取反，即使用共轭复数
        base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang));
        base w; // w: 当前旋转因子, w = (wn)^k

        // 遍历各个DFT块
        // i: 每个m点DFT块的起始索引
        for(int i = 0, j, k; i < n; i += m)
        {
            // 对每个m点DFT块进行蝶形运算
            // w初始化为1 (wn^0)
            // j: DFT块的前半部分索引
            // k: DFT块的后半部分索引起始 (i+l)
            for(w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn)
            {
                // t = w * p[j+l] (旋转因子乘以右半部分元素)
                base t = w * p[j + l];
                // p[j+l] = p[j] - t  (蝶形运算的下臂)
                p[j + l] = p[j] - t;
                // p[j] = p[j] + t    (蝶形运算的上臂)
                p[j] = p[j] + t;
            }
        }
    }

    // 3. IFFT的幅度调整
    // 如果是逆傅里叶变换，每个元素需要除以n
    if(inv)
    {
        for(int i = 0; i < n; ++i)
        {
            p[i].a /= n; // 实部除以n
            p[i].b /= n; // 虚部除以n (虽然理论上虚部应为0，但由于浮点误差可能不完全为0)
        }
    }
}

// 多项式乘法函数
// a, b: 输入的两个多项式的系数向量 (低次项在前)
// 返回值: 两个多项式相乘后得到的积多项式的系数向量
vector<long long> Multiply(vector<int> &a, vector<int> &b)
{
    // n, m: 分别是多项式a和b的系数个数 (即次数+1)
    int n = a.size(), m = b.size();
    // t: 结果多项式的系数个数上限 (deg(A*B) = deg(A) + deg(B))
    // (n-1) + (m-1) + 1 = n + m - 1
    int t = n + m - 1;
    int sz = 1; // sz: FFT所需的最小2的幂次长度

    // 确定FFT所需的长度sz，sz必须是2的幂且 sz >= t
    while(sz < t) sz <<= 1; // sz不断乘以2，直到大于等于t

    // 创建复数向量用于FFT
    vector<base> x(sz), y(sz), z(sz);

    // 1. 初始化FFT输入向量
    // 将多项式a的系数存入x，多项式b的系数存入y
    // 不足sz长度的部分用0填充 (隐式地，因为vector<base>默认构造为0+0i)
    for(int i = 0 ; i < sz; ++i)
    {
        // 如果i小于a的长度，则取a[i]作为实部，虚部为0
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        // 如果i小于b的长度，则取b[i]作为实部，虚部为0
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }

    // 2. 对两个多项式进行正向FFT (从系数表示转换到点值表示)
    fft(x); // 对x进行FFT
    fft(y); // 对y进行FFT

    // 3. 点值乘法
    // 在点值表示下，多项式乘法等价于对应点值的乘法
    // C(w_k) = A(w_k) * B(w_k)
    for(int i = 0; i < sz; ++i) z[i] = x[i] * y[i];

    // 4. 对乘积的点值表示进行逆向FFT (从点值表示转换回系数表示)
    fft(z, 1); // 1表示执行IFFT

    // 5. 提取结果
    // 结果多项式的系数应该是实数，并且是整数
    vector<long long> ret(sz); // 存储结果系数的向量
    for(int i = 0; i < sz; ++i)
    {
        // 取z[i]的实部，并四舍五入到最近的整数，以消除浮点误差
        // 系数可能很大，所以用long long存储
        ret[i] = (long long) round(z[i].a);
    }

    // 6. 调整结果向量的大小
    // 理论上结果多项式的系数个数是 t = a.size() + b.size() - 1
    // FFT可能会产生比t更多尾随0的系数（因为sz >= t）
    // 这里移除多余的尾随0，但确保结果向量的大小至少为1，
    // 并且不会移除使得结果小于理论最大长度 (t) 的0（除非整个多项式就是[0]）
    // 例如, 如果a=[1], b=[1], a.size()=1, b.size()=1, t=1. ret可能为[1,0,0,0] (sz=4).
    // 应该变成[1].
    // 如果a=[0], b=[0], t=1. ret可能为[0,0,0,0]. 应该变成[0].
    // 这个循环条件确保：
    // 1. ret.size() > 1: 避免将[0]这样的结果变成空向量
    // 2. ret.back() == 0: 只移除尾部的0
    // 3. ret.size() > a.size() + b.size() - 1: 确保不会将结果向量缩减到小于其理论最大长度t，
    //    除非更高次的系数确实都是0。这是为了处理sz远大于t的情况。
    //    一个更标准的做法可能是先 `ret.resize(t);` 然后再移除尾随0。
    while((int)ret.size() > 1 && ret.back() == 0 && ret.size() > (a.size() + b.size() - 1) )
    {
        ret.pop_back();
    }
    // 如果结果向量的长度大于等于t，并且尾部是0，则移除
    // 确保结果的长度是正确的，即最高次项系数非0
    // (或者如果整个多项式为0，则结果为[0])
    // 实际上，更简洁的做法是：
    // ret.resize(t); // 将结果向量调整到理论最大长度
    // while (ret.size() > 1 && ret.back() == 0) ret.pop_back(); // 移除尾部多余的0
    // if (ret.empty()) ret.push_back(0); // 如果是0多项式，确保结果是[0]
    // 但原始代码的逻辑是只在 sz > t 时才积极修剪，如果 sz == t，则保留 t 长度，即使有尾随0。
    // 除非 t=1 且 ret[0]=0，这种情况下会保留[0]。
    // 修正一下逻辑，使其更符合通常的多项式表示：结果的长度应为deg+1。
    // 如果结果多项式实际长度小于 t，则应去除尾随的0。
    // 正确的长度是 `t` (即 `a.size() + b.size() - 1`)
    ret.resize(t); // 首先将大小调整到理论上的最大项数
    while(ret.size() > 1 && ret.back() == 0) { // 然后移除高阶的0系数
        ret.pop_back();
    }
    if (ret.empty()) { // 如果所有系数都是0，例如 [0] * [0]
        ret.push_back(0); // 结果应该是 [0]
    }


    return ret;
}

// LeetCode 或类似平台的包装类
class Solution {
public:
    // 公开接口，调用实际的乘法函数
    vector<long long> multiply(vector<int>& poly1, vector<int>& poly2) {
        // 处理特殊情况：如果任一多项式为空（不规范的输入，但可以处理）
        // 或者如果任一多项式是零多项式 [0]
        if (poly1.empty() || poly2.empty()) {
            return {0}; // 或者根据题目要求返回空向量或抛出异常
        }
        if ((poly1.size() == 1 && poly1[0] == 0) || (poly2.size() == 1 && poly2[0] == 0)) {
            return {0}; // 任何多项式乘以零多项式结果为零多项式
        }
        return Multiply(poly1, poly2);
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {1, 2, 3}; // 1 + 2x + 3x^2
    vector<int> p2 = {4, 5};   // 4 + 5x

    // (1 + 2x + 3x^2) * (4 + 5x)
    // = 4 + 8x + 12x^2
    //     + 5x + 10x^2 + 15x^3
    // = 4 + 13x + 22x^2 + 15x^3
    // Coefficients: [4, 13, 22, 15]

    vector<long long> result = sol.multiply(p1, p2);

    cout << "Resultant polynomial coefficients: ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl; // Expected: 4 13 22 15

    vector<int> p3 = {0};
    vector<int> p4 = {1,2,3,4,5};
    result = sol.multiply(p3,p4);
    cout << "Resultant polynomial coefficients ([0] * P(x)): ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl; // Expected: 0

    vector<int> p5 = {1};
    vector<int> p6 = {5};
    result = sol.multiply(p5,p6);
    cout << "Resultant polynomial coefficients ([1] * [5]): ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl; // Expected: 5
    return 0;
}