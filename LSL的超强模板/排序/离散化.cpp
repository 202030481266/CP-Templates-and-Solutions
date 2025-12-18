#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstring>

using namespace std;

// 数据规模
const int N = 2000000;

// ==========================================
// 方法 1: 标准写法 (Sort + Unique + LowerBound)
// ==========================================
void discretize_standard(const vector<int>& raw, vector<int>& rank) {
    vector<int> vals = raw;

    // 1. Sort
    sort(vals.begin(), vals.end());

    // 2. Unique
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // 3. Lower_bound (Binary Search) -> 最大的性能瓶颈
    rank.resize(raw.size());
    for(size_t i = 0; i < raw.size(); ++i) {
        rank[i] = lower_bound(vals.begin(), vals.end(), raw[i]) - vals.begin() + 1;
    }
}

// ==========================================
// 方法 2: 离线 Pair 写法 (消除 LowerBound)
// ==========================================
void discretize_offline_pair(const vector<int>& raw, vector<int>& rank) {
    int n = raw.size();
    rank.resize(n);

    // 存储 {值, 原始下标}
    vector<pair<int, int>> p(n);
    for(int i = 0; i < n; ++i) {
        p[i] = {raw[i], i};
    }

    // 1. Sort Pairs
    sort(p.begin(), p.end());

    // 2. 线性扫描填表
    int cur_rank = 0;
    for(int i = 0; i < n; ++i) {
        if (i == 0 || p[i].first != p[i-1].first) {
            cur_rank++;
        }
        rank[p[i].second] = cur_rank;
    }
}

// ==========================================
// 方法 3: 基数排序 + 离线 (O(N) 极速版)
// ==========================================
// 简单的基数排序实现 (针对非负整数，支持负数需简单转换)
void radix_sort(vector<pair<int, int>>& a) {
    int n = a.size();
    vector<pair<int, int>> b(n);
    int cnt[256];

    // 32位整数，4次 pass，每次处理 8 bits
    for (int shift = 0; shift < 32; shift += 8) {
        memset(cnt, 0, sizeof(cnt));

        // 计数
        for (int i = 0; i < n; ++i)
            cnt[(a[i].first >> shift) & 0xFF]++;

        // 前缀和
        for (int i = 1; i < 256; ++i)
            cnt[i] += cnt[i - 1];

        // 倒序放入桶中以保持稳定性
        for (int i = n - 1; i >= 0; --i) {
            int byte = (a[i].first >> shift) & 0xFF;
            b[--cnt[byte]] = a[i];
        }

        a = b;
    }
}

void discretize_radix(const vector<int>& raw, vector<int>& rank) {
    int n = raw.size();
    rank.resize(n);

    vector<pair<int, int>> p(n);

    // 处理负数：基数排序通常处理无符号数，这里简单的加上偏移量转为正数处理
    // 实际通用库会处理符号位，这里为了演示逻辑简单化
    long long min_val = 0;
    for(int x : raw) if(x < min_val) min_val = x;

    for(int i = 0; i < n; ++i) {
        p[i] = {raw[i] - (int)min_val, i}; // 偏移为非负数
    }

    // 1. Radix Sort (O(N))
    radix_sort(p);

    // 2. 线性扫描
    int cur_rank = 0;
    for(int i = 0; i < n; ++i) {
        if (i == 0 || p[i].first != p[i-1].first) {
            cur_rank++;
        }
        rank[p[i].second] = cur_rank;
    }
}

// ==========================================
// 辅助函数
// ==========================================
void check_correctness(const vector<int>& r1, const vector<int>& r2) {
    for(size_t i=0; i<r1.size(); ++i) {
        if(r1[i] != r2[i]) {
            cout << "Result Mismatch at index " << i << "!" << endl;
            return;
        }
    }
    cout << "Correctness Check Passed." << endl;
}

int main() {
    // 准备数据
    vector<int> data(N);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // 使用较大的范围以模拟稀疏数据
    uniform_int_distribution<int> dist(0, N * 10);

    cout << "Generating " << N << " random numbers..." << endl;
    for(int i = 0; i < N; ++i) data[i] = dist(rng);

    vector<int> rank1, rank2, rank3;

    // 测试 1: Standard
    auto start = chrono::high_resolution_clock::now();
    discretize_standard(data, rank1);
    auto end = chrono::high_resolution_clock::now();
    cout << "Standard (Sort+Unique+LowerBound): "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    // 测试 2: Offline Pair
    start = chrono::high_resolution_clock::now();
    discretize_offline_pair(data, rank2);
    end = chrono::high_resolution_clock::now();
    cout << "Offline (Pair Sort + Linear Scan): "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    // 测试 3: Radix Sort
    start = chrono::high_resolution_clock::now();
    discretize_radix(data, rank3);
    end = chrono::high_resolution_clock::now();
    cout << "Radix (Radix Sort + Linear Scan):  "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    check_correctness(rank1, rank2);
    check_correctness(rank1, rank3);

    return 0;
}