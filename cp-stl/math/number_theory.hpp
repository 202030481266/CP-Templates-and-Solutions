#pragma once
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

namespace cp {
// GNU/Clang __int128 避免乘法溢出；mod > 0，exponent >= 0。
inline long long pow_mod(long long a, long long exponent, long long mod) {
    assert(mod > 0 && exponent >= 0);
    a %= mod;
    if (a < 0) a += mod;
    long long result = 1 % mod;
    while (exponent) {
        if (exponent & 1) result = static_cast<long long>((__int128)result * a % mod);
        a = static_cast<long long>((__int128)a * a % mod);
        exponent >>= 1;
    }
    return result;
}
// 逆元：支持非质数模数，gcd(a,mod)!=1 返回 nullopt，mod 必须 >1。
inline std::optional<long long> inverse_mod(long long a, long long mod) {
    assert(mod > 1);
    a %= mod;
    if (a < 0) a += mod;
    long long b = mod;
    __int128 x = 1, y = 0;
    while (b) {
        long long q = a / b, next = a % b;
        a = b; b = next;
        __int128 z = x - (__int128)q * y;
        x = y; y = z;
    }
    if (a != 1) return std::nullopt;
    x %= mod;
    if (x < 0) x += mod;
    return static_cast<long long>(x);
}
// 线性筛 O(n)，factorize(x) 只接受 1<=x<=n。
struct PrimeSieve {
    std::vector<int> primes, spf;
    explicit PrimeSieve(int n) : spf(n + 1) {
        for (int i = 2; i <= n; ++i) {
            if (!spf[i]) { spf[i] = i; primes.push_back(i); }
            for (int p : primes) {
                if (p > spf[i] || 1LL * p * i > n) break;
                spf[p * i] = p;
            }
        }
    }
    bool is_prime(int x) const {
        assert(0 <= x && x < int(spf.size()));
        return x >= 2 && spf[x] == x;
    }
    std::vector<std::pair<int, int>> factorize(int x) const {
        assert(1 <= x && x < int(spf.size()));
        std::vector<std::pair<int, int>> result;
        while (x > 1) {
            int p = spf[x], count = 0;
            do { x /= p; ++count; } while (x % p == 0);
            result.emplace_back(p, count);
        }
        return result;
    }
};
} // namespace cp
