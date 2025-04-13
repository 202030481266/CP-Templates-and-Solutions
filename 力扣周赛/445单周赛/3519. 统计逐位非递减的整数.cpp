#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


int dp[400][10];
int n, B;
string s;

std::pair<std::string, int> divideLargeString(const std::string& number, int divisor) {
    std::string quotient = "";
    long long current_remainder = 0; // Use long long for intermediate calculation
    bool leading_zero = true; // To handle leading zeros in the quotient

    for (char digit_char : number) {
        if (!isdigit(digit_char)) {
            throw std::invalid_argument("Input string contains non-digit characters.");
        }
        current_remainder = current_remainder * 10 + (digit_char - '0');
        int quotient_digit = current_remainder / divisor;

        if (quotient_digit > 0 || !leading_zero) {
            // Append digit only if it's non-zero or if we've already appended a non-zero digit
            quotient += std::to_string(quotient_digit);
            leading_zero = false;
        }
        current_remainder %= divisor;
    }

    // If the quotient is empty after the loop, it means the result is 0
    if (quotient.empty()) {
        quotient = "0";
    }

    return { quotient, static_cast<int>(current_remainder) };
}

// Function to convert a decimal string to a base-b string (2 <= b <= 62)
std::string decimalToBaseB(const std::string& decimalString, int b) {
    // --- Input Validation ---
    if (b < 2 || b > 62) {
        throw std::invalid_argument("Base must be between 2 and 62.");
    }
    if (decimalString.empty()) {
        throw std::invalid_argument("Input decimal string cannot be empty.");
    }
    // Check for negative sign (optional, this implementation assumes non-negative)
    if (decimalString[0] == '-') {
        throw std::invalid_argument("Negative numbers are not supported in this implementation.");
        // Or handle negative numbers if needed
    }
    // Handle zero case explicitly
    if (decimalString == "0") {
        return "0";
    }

    // --- Conversion Logic ---
    std::string digits = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "";
    std::string currentNumber = decimalString;
    int remainder;

    while (currentNumber != "0") {
        std::pair<std::string, int> divisionResult = divideLargeString(currentNumber, b);
        currentNumber = divisionResult.first;
        remainder = divisionResult.second;

        if (remainder < 0 || remainder >= b) {
            // This should theoretically not happen with correct division logic
            throw std::runtime_error("Internal error: Invalid remainder calculated.");
        }

        result += digits[remainder]; // Append the character for the remainder
    }

    // The result is built in reverse order (least significant digit first)
    std::reverse(result.begin(), result.end());

    return result;
}

class Solution {
public:
    int dfs(int p, int pre, bool is_limit, bool is_num) {
        if (p == n) return is_num;
        if (!is_limit && is_num && dp[p][pre] != -1) return dp[p][pre];
        int res = 0, up = (is_limit ? s[p] - '0' : B-1);
        if (!is_num) {
            res = (res + dfs(p+1, 0, false, false)) % mod;
            for (int i = 1; i <= up; ++i) {
                res = (res + dfs(p+1, i, is_limit && (i == up), true)) % mod;
            }
        }
        else {
            for (int i = pre; i <= up; ++i) {
                res = (res + dfs(p+1, i, is_limit && (i == up), true)) % mod;
            }
        }
        if (!is_limit && is_num) dp[p][pre] = res;
        return res;
    }
    
    int solve(const string& num) {
        s = decimalToBaseB(num, B);
        n = s.size();
        memset(dp, -1, sizeof(dp));
        return dfs(0, 0, true, false);
    }
    
    int countNumbers(string l, string r, int b) {
        B = b;
        int ans = (solve(r) - solve(l) + mod) % mod;
        int res = 1;
        string L = decimalToBaseB(l, b);
        for (int i = 0; i + 1 < L.size(); ++i) {
            if (L[i] > L[i+1]) {
                res = 0;
                break;
            }
        }
        return (ans + res) % mod;
    }
};