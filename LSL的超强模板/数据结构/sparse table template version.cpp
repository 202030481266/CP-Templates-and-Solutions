#include <vector>
#include <cmath>
#include <functional>

template<typename T, typename F>
struct ST {
    int N;
    std::vector<std::vector<T>> vec;
    F op;

    ST(const std::vector<T>& a, F _op) : N(a.size()), op(_op) {
        if (N == 0) return;
        int logN = std::log2(N) + 1;
        vec.assign(N, std::vector<T>(logN));
        for (int i = 0; i < N; ++i) {
            vec[i][0] = a[i];
        }
        ST_work();
    }

    void ST_work() {
        if (N == 0) return;
        int t = std::log2(N) + 1;
        for (int i = 1; i < t; ++i) {
            for (int j = 0; j + (1 << i) <= N; ++j) {
                vec[j][i] = op(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = std::log2(r - l + 1);
        return op(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};


void interval_max_example() {
    std::vector<int> data = {5, 2, 8, 1, 9, 4};
    
    // 定义最大值操作
    auto max_op = [](int a, int b) { return std::max(a, b); };

    // 实例化ST_max
    ST<int, decltype(max_op)> st_max(data, max_op);

    // 查询区间 [1, 4] 的最大值 (2, 8, 1, 9)
    std::cout << "Max in [1, 4]: " << st_max.query(1, 4) << std::endl; // 输出: 9
}

void interval_min_example() {
    std::vector<int> data = {5, 2, 8, 1, 9, 4};

    // 定义最小值操作
    auto min_op = [](int a, int b) { return std::min(a, b); };

    // 实例化ST_min
    ST<int, decltype(min_op)> st_min(data, min_op);

    // 查询区间 [1, 4] 的最小值 (2, 8, 1, 9)
    std::cout << "Min in [1, 4]: " << st_min.query(1, 4) << std::endl; // 输出: 1
}

void interval_gcd_example() {
    std::vector<long long> data = {12, 18, 30, 24};

    // 定义GCD操作
    auto gcd_op = [](long long a, long long b) { return std::gcd(a, b); };
    
    // 实例化ST_gcd
    ST<long long, decltype(gcd_op)> st_gcd(data, gcd_op);

    // 查询区间 [0, 2] 的最大公约数 gcd(12, 18, 30)
    std::cout << "GCD in [0, 2]: " << st_gcd.query(0, 2) << std::endl; // 输出: 6
}