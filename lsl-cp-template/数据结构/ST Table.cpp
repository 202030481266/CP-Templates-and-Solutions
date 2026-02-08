#include <bits/stdc++.h>
using namespace std;

// 0-index实现
template <typename T, class Op>
struct ST {
    int N;
    Op op;
    std::vector<std::vector<T>> vec;
    
    ST(int n, Op operation) : N(n), op(operation) {
        vec.assign(N + 1, vector<T>(30));
    }

    ST(const std::vector<T>& a, Op operation) : op(operation) {
        N = a.size();
        int max_log = std::__lg(N) + 1;
        vec.assign(N, std::vector<T>(max_log));
        for (int i = 0; i < N; i++) {
            vec[i][0] = a[i];
        }
        
        for (int i = 1; i < max_log; i++) {
            for (int j = 0; j + (1 << i) <= N; j++) {
                vec[j][i] = op(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = std::__lg(r - l + 1);
        return op(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

// 1-index实现
template <typename T, class Op>
struct ST {
    int N;
    Op op;
    std::vector<std::vector<T>> vec;
    
    ST(int n, Op operation) : N(n), op(operation) {
        vec.assign(N + 1, vector<T>(30));
    }

    ST(const std::vector<T>& a, Op operation) : op(operation) {
        N = a.size() - 1; // 假设 a[0] 是占位符
        int max_log = std::__lg(N) + 1;
        vec.assign(N + 1, std::vector<T>(max_log));
        for (int i = 1; i <= N; i++) {
            vec[i][0] = a[i];
        }

        for (int i = 1; i < max_log; i++) {
            for (int j = 1; j + (1 << i) - 1 <= N; j++) {
                vec[j][i] = op(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = std::__lg(r - l + 1);
        return op(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

// 区间最小值
auto min_op = [](int a, int b) { return min(a, b); };
ST<int, decltype(min_op)> st_min(arr, min_op);

// 区间最大值
auto max_op = [](int a, int b) { return max(a, b); };
ST<int, decltype(max_op)> st_max(arr, max_op);

// 区间GCD
auto gcd_op = [](int a, int b) { return __gcd(a, b); };
ST<int, decltype(gcd_op)> st_gcd(arr, gcd_op);


// 区间乘积或者和
#include <vector>
#include <cmath>
#include <iostream> // For cin in constructor
#include <numeric>  // For std::gcd, std::lcm if needed, though not for product

using namespace std;

// 这是一个求解区间乘积的取模的例子
struct ST {

    int N;
    long long k; // Modulus, should be long long if intermediate products can exceed int max before modulo
    vector<vector<long long>> vec; // Store products as long long to avoid overflow before modulo
    vector<int> log_table; // Optional: Precompute logs for efficiency

    ST() : N(0), k(0) {}

    // Constructor reading from cin
    ST(int n, long long modulus) : N(n), k(modulus) {
        vec.resize(N);
        int max_log = N > 0 ? floor(log2(N)) + 1 : 1;
        for (auto &v : vec) v.resize(max_log, 1); // Initialize with identity element for product (1)

        for (int i = 0; i < N; i++) {
            long long val;
            cin >> val;
            // Handle modulo k properly, especially for potentially negative inputs if allowed
            vec[i][0] = (val % k + k) % k; // Ensure non-negative result
        }
        ST_work();
        // precompute_logs(); // Optional
    }

    // Constructor from vector
    ST(const vector<int>& a, long long modulus) : N(a.size()), k(modulus) {
        if (N == 0) return;
        vec.resize(N);
        int max_log = floor(log2(N)) + 1;
        for (auto &v : vec) v.resize(max_log, 1);

        for (int i = 0; i < N; i++) {
            // Handle modulo k properly
            vec[i][0] = (static_cast<long long>(a[i]) % k + k) % k;
        }
        ST_work();
        // precompute_logs(); // Optional
    }

    // Optional: Precompute log base 2
    void precompute_logs() {
        log_table.resize(N + 1);
        log_table[1] = 0;
        for (int i = 2; i <= N; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }
    }

    // Get log base 2 (using precomputation or cmath::log2)
    int get_log2(int n) {
        if (!log_table.empty()) {
             // Handle n=0 case if necessary, though length is usually >= 1
             return n > 0 ? log_table[n] : -1;
        } else {
            return n > 0 ? floor(log2(n)) : -1;
        }
    }


    void ST_work() {
        if (N == 0) return;
        int t = floor(log2(N)) + 1; // Calculate max power needed
        for (int i = 1; i < t; i++) {
            for (int j = 0; j + (1 << i) <= N; j++) { // Ensure the second interval is within bounds
                // Careful with potential overflow before modulo if k is large
                vec[j][i] = (vec[j][i - 1] * vec[j + (1 << (i - 1))][i - 1]) % k;
            }
        }
    }

    // O(log N) query for product
    long long query(int l, int r) {
        if (l < 0 || r >= N || l > r) {
            // Handle invalid range - return identity element or throw error
            return 1; // Identity for multiplication
        }

        long long ans = 1; // Initialize result with identity element for multiplication
        int max_log = floor(log2(N)) +1 ; // Or use precomputed max_log

        // Iterate through powers of 2, from largest down to smallest
        for (int j = max_log; j >= 0; j--) {
            // Check if an interval of size 2^j starting at l fits within the *remaining* query range [l, r]
            if (l + (1 << j) - 1 <= r) {
                 // Multiply the result by the precomputed product of the interval [l, l + 2^j - 1]
                ans = (ans * vec[l][j]) % k;
                // Move the left boundary past the interval we just processed
                l += (1 << j);
            }
        }
        // After the loop, l should be r + 1 if the logic is correct
        // The final result is accumulated in 'ans'
        return ans;
    }
};

// Example Usage:
int main() {
    vector<int> arr = {2, 3, 4, 5, 6};
    long long modulus = 1000; // Example modulus

    ST st_table(arr, modulus);

    // Query product of range [1, 3] (elements arr[1], arr[2], arr[3] -> 3, 4, 5)
    // Expected: (3 * 4 * 5) % 1000 = 60 % 1000 = 60
    cout << "Product of [1, 3]: " << st_table.query(1, 3) << endl; // Output: 60

    // Query product of range [0, 4] (all elements -> 2, 3, 4, 5, 6)
    // Expected: (2 * 3 * 4 * 5 * 6) % 1000 = 720 % 1000 = 720
    cout << "Product of [0, 4]: " << st_table.query(0, 4) << endl; // Output: 720

     // Query product of range [2, 2] (element arr[2] -> 4)
    // Expected: 4 % 1000 = 4
    cout << "Product of [2, 2]: " << st_table.query(2, 2) << endl; // Output: 4

    vector<int> arr_with_zero = {2, 3, 0, 5, 6};
    ST st_table_zero(arr_with_zero, modulus);
     // Query product of range [1, 3] (elements 3, 0, 5)
    // Expected: (3 * 0 * 5) % 1000 = 0
    cout << "Product of [1, 3] (with zero): " << st_table_zero.query(1, 3) << endl; // Output: 0


    return 0;
}