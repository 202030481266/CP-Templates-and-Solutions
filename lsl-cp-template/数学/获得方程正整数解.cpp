// ax + by = c的正整数解问题
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct Solution {
    bool has_solution;
    ll x, y;
};

// 辅助函数：向下取整除法 floor(a/b)
// 适用于 b > 0 的情况
ll div_floor(ll a, ll b) {
    if (a % b == 0) return a / b;
    if (a < 0) return a / b - 1; // 负数不能直接除，如 -5/3 = -1 但 floor是 -2
    return a / b;
}

// 辅助函数：向上取整除法 ceil(a/b)
// 适用于 b > 0 的情况
ll div_ceil(ll a, ll b) {
    if (a % b == 0) return a / b;
    if (a > 0) return a / b + 1;
    return a / b;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

/**
 * 求解 ax + by = c，且满足 x in [lx, rx], y in [ly, ry]
 * @param a, b 系数 (需为正整数)
 * @param c 常数
 * @param lx, rx  x 的取值范围
 * @param ly, ry  y 的取值范围
 */
Solution solve_bounded(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
    ll x0, y0;
    ll g = exgcd(a, b, x0, y0);
    
    // 1. 裴蜀定理检查
    if (c % g != 0) return {false, 0, 0};

    // 2. 构造特解 (x0, y0) -> (x1, y1)
    x0 *= c / g;
    y0 *= c / g;

    // 3. 计算步长 (注意 a, b 必须为正)
    ll dx = b / g;
    ll dy = a / g;

    // 4. 求解 k 的范围
    // 通解: x = x0 + k * dx,  y = y0 - k * dy
    
    // (A) 限制 x: lx <= x0 + k*dx <= rx
    // => (lx - x0)/dx <= k <= (rx - x0)/dx
    ll k_min_x = div_ceil(lx - x0, dx);
    ll k_max_x = div_floor(rx - x0, dx);

    // (B) 限制 y: ly <= y0 - k*dy <= ry
    // => ly - y0 <= -k*dy <= ry - y0
    // => y0 - ry <= k*dy <= y0 - ly  (两边同乘-1，不等号翻转，移项)
    // => (y0 - ry)/dy <= k <= (y0 - ly)/dy
    ll k_min_y = div_ceil(y0 - ry, dy);
    ll k_max_y = div_floor(y0 - ly, dy);

    // 5. 求交集
    ll k_start = max(k_min_x, k_min_y);
    ll k_end   = min(k_max_x, k_max_y);

    if (k_start > k_end) {
        return {false, 0, 0}; // 交集为空，无解
    }

    // 6. 构造具体解
    // 既然只要一个解，我们取 k_start 即可 (这通常对应最小的 x)
    ll k = k_start; 
    return {true, x0 + k * dx, y0 - k * dy};
}

int main() {
    // 场景一：你的原始需求，正整数解 (x >= 1, y >= 1)
    // 设定极大值为 2e18 防止溢出即可
    ll INF = 2e18; 
    
    // 例子 1: 3x + 5y = 21, 求正整数解
    Solution res1 = solve_bounded(3, 5, 21, 1, INF, 1, INF);
    if (res1.has_solution) cout << "Ex1: x=" << res1.x << ", y=" << res1.y << endl;
    else cout << "Ex1: No Solution" << endl;

    // 例子 2: 3x + 5y = 7, 求正整数解
    Solution res2 = solve_bounded(3, 5, 7, 1, INF, 1, INF);
    if (res2.has_solution) cout << "Ex2: x=" << res2.x << ", y=" << res2.y << endl;
    else cout << "Ex2: No Solution" << endl;

    // 场景二：特定区间
    // 例子 3: x + y = 10, x在[6, 8]之间, y在[0, 10]之间
    // 显然 x=6,y=4; x=7,y=3; x=8,y=2 都是解。
    // 该算法会返回 x 最小的那个解 (x=6)
    Solution res3 = solve_bounded(1, 1, 10, 6, 8, 0, 10);
    if (res3.has_solution) cout << "Ex3: x=" << res3.x << ", y=" << res3.y << endl;
    else cout << "Ex3: No Solution" << endl;

    return 0;
}