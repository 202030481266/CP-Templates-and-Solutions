// 巧妙的差分构造
// 在一般的区间差分中，如果同时加上一个数字，a(i+1)-ai的差值是不变，其本质为 A-A=0
// fibnacci中不能这样子维护，但是 fi-f(i-1)-f(i-2)的差值是可以等于0，所以我们构造 Di = Ci - Ci-1 - Ci-2

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 100;
long long fib_seq[N]; // 存储斐波那契数列
long long D[N];       // 我们的魔法差分数组 D
int notzero = 0;      // 记录 D 中非零元素的个数
int MOD;
int n, q;

// 封装后的更新函数，负责安全地更新单点，并自动维护非零计数器
void update_D(int index, long long delta) {
    if (index >= n) return; // 如果超出了数组边界，直接忽略，不用再在主逻辑里写一堆 if

    // 1. 如果更新前不是 0，先从计数器中减去
    if (D[index] != 0) notzero--;

    // 2. 执行加法并取模 (保证结果是正数)
    D[index] = (D[index] + delta) % MOD;
    if (D[index] < 0) D[index] += MOD;

    // 3. 如果更新后不是 0，重新加回计数器
    if (D[index] != 0) notzero++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> MOD;

    // 预处理斐波那契数列 (为了和公式 100% 对齐，这里采用 1-based 的思维)
    // fib_seq[1] = 1, fib_seq[2] = 1, fib_seq[3] = 2 ...
    fib_seq[1] = 1;
    fib_seq[2] = 1;
    for (int i = 3; i < N; i++) {
        fib_seq[i] = (fib_seq[i - 1] + fib_seq[i - 2]) % MOD;
    }

    vector<long long> A(n), B(n), C(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    
    // 初始化 C 数组： C = A - B
    for (int i = 0; i < n; i++) {
        C[i] = (A[i] - B[i]) % MOD;
        if (C[i] < 0) C[i] += MOD;
    }

    // 初始化魔法差分数组 D: D[i] = C[i] - C[i-1] - C[i-2]
    for (int i = 0; i < n; i++) {
        long long c_i = C[i];
        long long c_i_minus_1 = (i >= 1) ? C[i - 1] : 0;
        long long c_i_minus_2 = (i >= 2) ? C[i - 2] : 0;
        
        long long init_val = (c_i - c_i_minus_1 - c_i_minus_2) % MOD;
        update_D(i, init_val); 
    }

    // 处理查询
    while (q--) {
        char type;
        int l, r;
        cin >> type >> l >> r;
        
        // 转换成 0-based 索引
        l--; 
        r--;
        
        // 区间长度
        int len = r - l + 1;

        if (type == 'A') { // 给 A 数组加上斐波那契数列
            update_D(l, 1);                                 // D[l] 增加 F_1
            update_D(r + 1, -fib_seq[len + 1]);             // D[r+1] 减去 F_{len+1}
            update_D(r + 2, -fib_seq[len]);                 // D[r+2] 减去 F_{len}
        } else {           // 给 B 数组加上斐波那契数列 (相当于 A 减去)
            update_D(l, -1);
            update_D(r + 1, fib_seq[len + 1]);
            update_D(r + 2, fib_seq[len]);
        }

        // $O(1)$ 的终极判断
        if (notzero == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}