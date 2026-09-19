#pragma once
#include <cassert>
#include <limits>

namespace cp {
// [lo,hi) 中找第一个为真的位置；check 单调 false -> true，无解返回 hi。
// 使用 __int128 计算中点，支持完整 long long 边界。
template<class F>
long long first_true(long long lo, long long hi, F check) {
    assert(lo <= hi);
    while (lo < hi) {
        long long mid = static_cast<long long>((__int128)lo + ((__int128)hi - lo) / 2);
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// 支持负数；排除除零和 LLONG_MIN / -1（结果超出 long long）。
inline long long floor_div(long long a, long long b) {
    assert(b != 0 && !(a == std::numeric_limits<long long>::min() && b == -1));
    long long q = a / b, r = a % b;
    return q - (r != 0 && ((r > 0) != (b > 0)));
}
inline long long ceil_div(long long a, long long b) {
    assert(b != 0 && !(a == std::numeric_limits<long long>::min() && b == -1));
    long long q = a / b, r = a % b;
    return q + (r != 0 && ((r > 0) == (b > 0)));
}
} // namespace cp
