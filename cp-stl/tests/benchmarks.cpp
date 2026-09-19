// Reproducible microbenchmarks. See benchmark.py and docs/performance.md.
// Data generation and stdout are outside the timed regions; each case is warmed once.
#include <bits/stdc++.h>
#include "data_structures/dsu.hpp"
#include "data_structures/fenwick.hpp"
#include "data_structures/segment_tree.hpp"
#include "data_structures/lazy_segment_tree.hpp"
#include "data_structures/xor_basis.hpp"
#include "graph/shortest_path.hpp"
#include "graph/scc.hpp"
#include "math/modint.hpp"
#include "math/matrix.hpp"
#include "string/rolling_hash.hpp"
#include "string/aho_corasick.hpp"
#include "string/kmp.hpp"

using u64 = std::uint64_t;
using Clock = std::chrono::steady_clock;
volatile u64 benchmark_sink = 0;

template<class F>
void measure(const char* name, F run) {
    u64 expected = run();
    benchmark_sink = benchmark_sink ^ expected;
    auto start = Clock::now();
    u64 actual = run();
    auto end = Clock::now();
    benchmark_sink = benchmark_sink ^ actual;
    if (expected != actual) throw std::runtime_error(std::string("Unstable checksum: ") + name);
    double milliseconds = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << name << ',' << std::fixed << std::setprecision(6)
              << milliseconds << ',' << actual << '\n';
}

struct Operation { int l, r; long long value; };

int main() {
    std::mt19937_64 random(20260919);
    cp::XorBasis basis;
    for (int bit = 0; bit < 60; ++bit)
        basis.insert((u64{1} << bit) | (random() & ((u64{1} << bit) - 1)));
    std::vector<u64> ranks(50000);
    for (auto& rank : ranks) rank = random() & ((u64{1} << 60) - 1);
    measure("xor_kth_rank60_q50000", [&] {
        u64 checksum = 0;
        for (u64 rank : ranks) checksum += basis.kth(rank).value();
        return checksum;
    });

    using M = cp::Mint;
    std::vector<M> addends(4096);
    for (auto& value : addends) value = M(random() % M::mod());
    measure("modint_add_10000000", [&] {
        M sum = 0;
        for (int i = 0; i < 10000000; ++i) sum += addends[i & 4095];
        return u64(sum.val());
    });
    std::vector<std::pair<M, long long>> powers(100000);
    for (auto& [value, exponent] : powers) {
        value = M(random() % M::mod());
        exponent = static_cast<long long>(random() % 1000000001);
    }
    measure("modint_pow_q100000", [&] {
        u64 checksum = 0;
        for (auto [value, exponent] : powers) checksum += value.pow(exponent).val();
        return checksum;
    });

    cp::Matrix<u64> small_power(160);
    for (auto& row : small_power.a) for (auto& x : row) x = random() % 100;
    measure("matrix_u64_n160_pow1_x8", [&] {
        u64 checksum = 0;
        for (int repeat = 0; repeat < 8; ++repeat) {
            auto result = small_power.pow(1);
            for (const auto& row : result.a) for (auto x : row) checksum += x;
        }
        return checksum;
    });
    cp::Matrix<M> large_power(40);
    for (auto& row : large_power.a) for (auto& x : row) x = M(random() % 100);
    measure("matrix_mint_n40_pow1e9_x3", [&] {
        u64 checksum = 0;
        for (int repeat = 0; repeat < 3; ++repeat) {
            auto result = large_power.pow(1000000000);
            for (const auto& row : result.a) for (auto x : row) checksum += x.val();
        }
        return checksum;
    });

    constexpr int n = 200000, q = 200000;
    std::vector<long long> array(n);
    for (auto& x : array) x = static_cast<long long>(random() % 1000);
    std::vector<Operation> operations(q);
    for (auto& op : operations) {
        op.l = int(random() % n);
        op.r = op.l + 1 + int(random() % (n - op.l));
        op.value = static_cast<long long>(random() % 11) - 5;
    }
    measure("lazy_build_read_n200000_q200000", [&] {
        cp::RangeAddSum tree(array);
        u64 checksum = 0;
        for (auto op : operations) checksum += u64(tree.sum(op.l, op.r));
        return checksum;
    });
    measure("lazy_build_mixed_n200000_q200000", [&] {
        cp::RangeAddSum tree(array);
        u64 checksum = 0;
        for (int i = 0; i < q; ++i) {
            auto op = operations[i];
            if (i & 1) checksum += u64(tree.sum(op.l, op.r));
            else tree.add(op.l, op.r, op.value);
        }
        return checksum;
    });
    measure("fenwick_build_mixed_n200000_q200000", [&] {
        cp::Fenwick<long long> tree(array);
        u64 checksum = 0;
        for (int i = 0; i < q; ++i) {
            auto op = operations[i];
            if (i & 1) checksum += u64(tree.sum(op.l, op.r));
            else tree.add(op.l, op.value);
        }
        return checksum;
    });
    measure("segment_build_mixed_n200000_q200000", [&] {
        cp::SegmentTree<long long, std::plus<long long>> tree(array, 0);
        u64 checksum = 0;
        for (int i = 0; i < q; ++i) {
            auto op = operations[i];
            if (i & 1) checksum += u64(tree.prod(op.l, op.r));
            else tree.set(op.l, op.value);
        }
        return checksum;
    });
    measure("dsu_build_merge_n200000_q200000", [&] {
        cp::DSU dsu(n);
        u64 checksum = 0;
        for (auto op : operations) {
            checksum += dsu.merge(op.l, op.r - 1);
            checksum += dsu.size(op.l);
        }
        return checksum;
    });

    std::string text(1000000, 'a');
    for (char& c : text) c += char(random() % 26);
    measure("rolling_hash_build_n1000000", [&] {
        cp::RollingHash hash(text);
        auto result = hash.get(0, int(text.size()));
        return u64(result[0]) + u64(result[1]);
    });
    cp::RollingHash hash(text);
    measure("rolling_hash_query_n1000000_q200000", [&] {
        u64 checksum = 0;
        for (auto op : operations) {
            auto result = hash.get(op.l * 4, op.r * 4);
            checksum += u64(result[0]) + u64(result[1]);
        }
        return checksum;
    });
    std::string repetitive(1000000, 'a');
    measure("kmp_n1000000_pattern100_matches999901", [&] {
        auto result = cp::kmp_find(repetitive, std::string(100, 'a'));
        u64 checksum = result.size();
        for (int p : result) checksum += u64(p);
        return checksum;
    });
    std::vector<std::string> patterns(10000, std::string(12, 'a'));
    for (auto& pattern : patterns) for (char& c : pattern) c += char(random() % 26);
    measure("ac_10000_patterns_len12_text1e6", [&] {
        cp::AhoCorasick ac;
        for (const auto& pattern : patterns) ac.insert(pattern);
        ac.build();
        auto counts = ac.count(text);
        u64 checksum = counts.size();
        for (auto count : counts) checksum += u64(count);
        return checksum;
    });

    constexpr int vertices = 100000, edges = 300000;
    cp::WeightedGraph weighted(vertices);
    std::vector<std::vector<int>> directed(vertices);
    for (int i = 0; i < edges; ++i) {
        int u = i < vertices - 1 ? i : int(random() % vertices);
        int v = i < vertices - 1 ? i + 1 : int(random() % vertices);
        weighted[u].push_back({v, static_cast<long long>(1 + random() % 100)});
        directed[u].push_back(v);
    }
    measure("dijkstra_n100000_m300000", [&] {
        auto distances = cp::dijkstra(weighted, 0);
        u64 checksum = 0;
        for (auto distance : distances) checksum += u64(distance);
        return checksum;
    });
    measure("scc_n100000_m300000", [&] {
        auto result = cp::strongly_connected_components(directed);
        u64 checksum = result.groups.size();
        for (int id : result.id) checksum += u64(id);
        return checksum;
    });
}
