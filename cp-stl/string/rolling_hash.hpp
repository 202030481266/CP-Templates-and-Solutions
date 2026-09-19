#pragma once
#include <array>
#include <cassert>
#include <string_view>
#include <vector>

namespace cp {
// 双模前缀哈希；预处理 O(n)，get(l,r) O(1)，区间 [l,r)。
// 不同对象可比较（使用相同 base）。概率算法，不能作为绝无碰撞的证明。
// 文本按字节处理；比较子串时还须检查长度相同。
class RollingHash {
    static constexpr std::array<long long, 2> mod_{1000000007, 1000000009};
    static constexpr long long base_ = 911382323;
    std::vector<std::array<long long, 2>> hash_, power_;
public:
    explicit RollingHash(std::string_view s) : hash_(s.size() + 1), power_(s.size() + 1) {
        power_[0] = {1, 1};
        for (std::size_t i = 0; i < s.size(); ++i)
            for (int j = 0; j < 2; ++j) {
                power_[i + 1][j] = power_[i][j] * base_ % mod_[j];
                hash_[i + 1][j] = (hash_[i][j] * base_ + static_cast<unsigned char>(s[i]) + 1) % mod_[j];
            }
    }
    std::array<long long, 2> get(int l, int r) const {
        assert(0 <= l && l <= r && r < int(hash_.size()));
        std::array<long long, 2> answer{};
        for (int j = 0; j < 2; ++j)
            answer[j] = (hash_[r][j] - hash_[l][j] * power_[r - l][j] % mod_[j] + mod_[j]) % mod_[j];
        return answer;
    }
};
} // namespace cp
