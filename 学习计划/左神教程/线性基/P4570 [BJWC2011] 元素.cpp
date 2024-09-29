#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Mineral {
    uint64_t number;
    int magic;
};

int main() {
    int N;
    std::cin >> N;
    std::vector<Mineral> minerals(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> minerals[i].number >> minerals[i].magic;
    }

    // Sort minerals in decreasing order of magic power
    std::sort(minerals.begin(), minerals.end(), [](const Mineral& a, const Mineral& b) {
        return a.magic > b.magic;
    });

    uint64_t basis[64] = {0};
    int64_t totalMagic = 0;

    for (const auto& mineral : minerals) {
        uint64_t v = mineral.number;
        uint64_t originalV = v;
        for (int i = 63; i >= 0; --i) {
            if (v & (1ULL << i)) {
                if (basis[i] == 0) {
                    basis[i] = v;
                    totalMagic += mineral.magic;
                    break;
                } else {
                    v ^= basis[i];
                }
            }
        }
    }

    std::cout << totalMagic << std::endl;

    return 0;
}