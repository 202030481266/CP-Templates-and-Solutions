#include <bits/stdc++.h>
using namespace std;

// 向下取整的除法
long long floor_div(long long a, long long b) {
    long long q = a / b;
    long long r = a % b;
    // 检查余数不为0且a和b符号相反
    if (r != 0 && ((a ^ b) < 0)) {
        q -= 1;
    }
    return q;
}

// 向上取整的除法
long long ceil_div(long long a, long long b) {
    long long q = a / b;
    long long r = a % b;
    // 检查余数不为0且a和b符号相同
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}

// 扩展欧几里得算法
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

// 示例主函数
int main() {
    // 示例使用
    long long a = 10, b = 3;
    cout << "floor_div(" << a << ", " << b << ") = " << floor_div(a, b) << endl;
    cout << "ceil_div(" << a << ", " << b << ") = " << ceil_div(a, b) << endl;

    long long x, y;
    long long gcd = extendedGCD(a, b, x, y);
    cout << "GCD(" << a << ", " << b << ") = " << gcd << endl;
    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}
