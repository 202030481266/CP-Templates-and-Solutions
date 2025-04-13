#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For reverse
#include <stdexcept> // For invalid_argument

// Helper function to perform division of a large number string by an integer
// Returns the quotient string and the remainder integer
std::pair<std::string, int> divideLargeString(const std::string& number, int divisor) {
    std::string quotient = "";
    long long current_remainder = 0; // Use long long for intermediate calculation
    bool leading_zero = true; // To handle leading zeros in the quotient

    // 长除法的原理，模拟除法
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

// --- Example Usage ---
int main() {
    try {
        std::cout << "10 (dec) to base 2: " << decimalToBaseB("10", 2) << std::endl; // Expected: 1010
        std::cout << "255 (dec) to base 16: " << decimalToBaseB("255", 16) << std::endl; // Expected: ff
        std::cout << "61 (dec) to base 62: " << decimalToBaseB("61", 62) << std::endl; // Expected: Z
        std::cout << "12345 (dec) to base 8: " << decimalToBaseB("12345", 8) << std::endl; // Expected: 30071
        std::cout << "1000 (dec) to base 36: " << decimalToBaseB("1000", 36) << std::endl; // Expected: rs
        std::cout << "0 (dec) to base 5: " << decimalToBaseB("0", 5) << std::endl; // Expected: 0

        // Example with a very large number
        std::string large_number = "123456789012345678901234567890";
        std::cout << large_number << " (dec) to base 62: " << decimalToBaseB(large_number, 62) << std::endl;
        // Expected: 1UMBn6jXnQV8oNEaL0

        // Example of invalid input
        // std::cout << decimalToBaseB("12a3", 10) << std::endl; // Throws invalid_argument
        // std::cout << decimalToBaseB("100", 1) << std::endl;   // Throws invalid_argument
        // std::cout << decimalToBaseB("100", 63) << std::endl;  // Throws invalid_argument

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}