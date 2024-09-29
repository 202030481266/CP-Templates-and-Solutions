#include <iostream>
#include <type_traits>

// Existing my_builtin_clz functions
int my_builtin_clz(unsigned int x) {
    if (x == 0) return 32;
    int n = 0;
    if ((x & 0xFFFF0000U) == 0) { n += 16; x <<= 16; }
    if ((x & 0xFF000000U) == 0) { n += 8; x <<= 8; }
    if ((x & 0xF0000000U) == 0) { n += 4; x <<= 4; }
    if ((x & 0xC0000000U) == 0) { n += 2; x <<= 2; }
    if ((x & 0x80000000U) == 0) { n += 1; }
    return n;
}

int my_builtin_clz(int x) {
    return my_builtin_clz(static_cast<unsigned int>(x));
}

int my_builtin_clz(unsigned long long x) {
    if (x == 0) return 64;
    int n = 0;
    if ((x & 0xFFFFFFFF00000000ULL) == 0) { n += 32; x <<= 32; }
    if ((x & 0xFFFF000000000000ULL) == 0) { n += 16; x <<= 16; }
    if ((x & 0xFF00000000000000ULL) == 0) { n += 8; x <<= 8; }
    if ((x & 0xF000000000000000ULL) == 0) { n += 4; x <<= 4; }
    if ((x & 0xC000000000000000ULL) == 0) { n += 2; x <<= 2; }
    if ((x & 0x8000000000000000ULL) == 0) { n += 1; }
    return n;
}

int my_builtin_clz(long long x) {
    return my_builtin_clz(static_cast<unsigned long long>(x));
}

// Function to compute the MSB position
template<typename T>
int compute_msb_pos(T x) {
    using UnsignedT = typename std::make_unsigned<T>::type;
    UnsignedT ux = static_cast<UnsignedT>(x);

    if (ux == 0) return -1; // Undefined for zero

    int total_bits = sizeof(T) * 8;
    int leading_zeros = my_builtin_clz(ux);
    int msb_pos = (total_bits - 1) - leading_zeros;

    return msb_pos;
}

// Example usage
int main() {
    unsigned int ui = 0x00F0;     // 240 in decimal
    int i = 0x00F0;               // 240 in decimal
    unsigned long long ull = 0x0000FF00ULL; // 65280 in decimal
    long long ll = 0x0000FF00LL;  // 65280 in decimal

    unsigned int test_value = 4;  // Test value to check MSB position

    std::cout << "MSB position of ui: " << compute_msb_pos(ui) << std::endl;
    std::cout << "MSB position of i: " << compute_msb_pos(i) << std::endl;
    std::cout << "MSB position of ull: " << compute_msb_pos(ull) << std::endl;
    std::cout << "MSB position of ll: " << compute_msb_pos(ll) << std::endl;
    std::cout << "MSB position of test_value (4): " << compute_msb_pos(test_value) << std::endl;

    return 0;
}
