#include <bits/stdc++.h>
#include <unordered_map>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// 自定义哈希函数，防止哈希碰撞攻击
struct custom_hash {
    // splitmix64 算法，用于生成高质量的哈希值
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    // 重载函数调用运算符，生成最终的哈希值
    size_t operator()(uint64_t x) const {
        // FIXED_RANDOM 用于随机化哈希函数，增加安全性
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// 定义使用自定义哈希的 unordered_map
typedef unordered_map<long long, int, custom_hash> safe_map_t;

// 定义使用自定义哈希的 gp_hash_table
typedef gp_hash_table<long long, int, custom_hash> safe_hash_table_t;

// 全局变量，用于测试
const int N = 200000;

// 测试标准 unordered_map
void test_unordered_map(long long x) {
    auto begin = chrono::high_resolution_clock::now();

    unordered_map<long long, int> numbers;
    numbers.reserve(N); // 预留空间，减少重哈希的开销

    for (int i = 1; i <= N; i++) {
        numbers[i * x] = i;
    }

    long long sum = 0;
    for (auto &entry : numbers) {
        sum += (entry.first / x) * entry.second;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    printf("unordered_map - x = %lld: %.3lf seconds, sum = %lld\n", x, elapsed.count(), sum);
}

// 测试使用自定义哈希的 unordered_map
void test_safe_map(long long x) {
    auto begin = chrono::high_resolution_clock::now();

    safe_map_t numbers;
    numbers.reserve(N); // 预留空间

    for (int i = 1; i <= N; i++) {
        numbers[i * x] = i;
    }

    long long sum = 0;
    for (auto &entry : numbers) {
        sum += (entry.first / x) * entry.second;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    printf("safe_map     - x = %lld: %.3lf seconds, sum = %lld\n", x, elapsed.count(), sum);
}

// 测试 gp_hash_table
void test_gp_hash_table(long long x) {
    auto begin = chrono::high_resolution_clock::now();

    safe_hash_table_t numbers;
    numbers.reserve(N); // 预留空间

    for (int i = 1; i <= N; i++) {
        numbers[i * x] = i;
    }

    long long sum = 0;
    for (auto &entry : numbers) {
        sum += (entry.first / x) * entry.second;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    printf("gp_hash_table - x = %lld: %.3lf seconds, sum = %lld\n", x, elapsed.count(), sum);
}

int main() {
    // 设置同步关闭，提高 I/O 性能（如果有需要）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 测试不同的 x 值
    vector<long long> test_values = {107897, 126271};

    for (auto x : test_values) {
        printf("Testing with x = %lld\n", x);
        test_unordered_map(x);
        test_safe_map(x);
        test_gp_hash_table(x);
        printf("---------------------------------------------------\n");
    }

    return 0;
}
