#include <array>
#include <vector>
#include <algorithm>
#include <cstddef>

template <size_t MaxBits = 60, typename T = unsigned long long>
class LinearBasis {
private:
    std::array<T, MaxBits + 1> basis{};
    std::vector<T> rebuilt_basis; // 用于求解第 K 小异或和
    size_t rank = 0;              // 线性基的秩（有效基底数量）
    bool has_zero = false;        // 是否出现过线性相关（能否异或出 0）
    bool is_rebuilt = false;      // 重构标记，用于懒加载

    // 重构线性基：让每个基底的二进制位彼此独立（化为对角矩阵），用于查询第 K 小
    void rebuild() {
        if (is_rebuilt) return;
        std::array<T, MaxBits + 1> temp = basis;
        for (int i = MaxBits; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if ((temp[i] >> j) & 1) {
                    temp[i] ^= temp[j];
                }
            }
        }
        rebuilt_basis.clear();
        for (int i = 0; i <= MaxBits; ++i) {
            if (temp[i]) rebuilt_basis.push_back(temp[i]);
        }
        is_rebuilt = true;
    }

public:
    LinearBasis() = default;

    // 1. 插入元素
    // 返回值：true 表示成功作为新基底插入；false 表示被现有基底消元为 0（线性相关）
    bool insert(T x) {
        is_rebuilt = false; // 破坏了重构状态
        for (int i = MaxBits; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    rank++;
                    return true;
                }
                x ^= basis[i];
            }
        }
        has_zero = true; // x 被完全消元，说明原集合能异或出 0
        return false;
    }

    // 2. 查询能否异或出目标值 x
    bool can_represent(T x) const {
        if (x == 0) return has_zero;
        for (int i = MaxBits; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (!basis[i]) return false;
                x ^= basis[i];
            }
        }
        return true;
    }

    // 3. 查询最大异或和
    // optional_initial: 允许传入一个初始值与其进行异或最大化
    T max_xor(T initial = 0) const {
        T res = initial;
        for (int i = MaxBits; i >= 0; --i) {
            res = std::max(res, res ^ basis[i]);
        }
        return res;
    }

    // 4. 查询最小异或和
    // 规定：如果原集合能异或出 0，则最小异或和为 0；否则为最小的非零基底
    T min_xor() const {
        if (has_zero) return 0;
        for (int i = 0; i <= MaxBits; ++i) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }

    // 5. 查询第 K 小异或和（去重后的第 K 小）
    // 返回 -1 (或对于无符号类型的最大值) 表示 K 超出了可表出的集合大小
    T kth_xor(T k) {
        if (has_zero) --k; // 如果能异或出 0，那么 0 就是第 1 小，消耗掉一个 k
        if (k == 0) return 0;
        
        rebuild(); // 懒加载重构
        
        if (k >= (static_cast<T>(1) << rank)) return static_cast<T>(-1); // 无解

        T res = 0;
        for (size_t i = 0; i < rebuilt_basis.size(); ++i) {
            if ((k >> i) & 1) {
                res ^= rebuilt_basis[i];
            }
        }
        return res;
    }

    // 获取当前线性基的秩
    size_t get_rank() const { return rank; }
};