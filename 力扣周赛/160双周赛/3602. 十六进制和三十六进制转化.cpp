#include <string>
#include <algorithm>
#include <vector>

class Solution {
public:
    std::string concatHex36(int n) {
        auto toBase = [](long long num, int base) {
            if (num == 0) {
                return std::string("0");
            }
            const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            std::string result;
            while (num > 0) {
                result += digits[num % base];
                num /= base;
            }
            std::reverse(result.begin(), result.end());
            return result;
        };

        long long val = n;
        long long n2 = val * val;
        long long n3 = n2 * val;

        return toBase(n2, 16) + toBase(n3, 36);
    }
};