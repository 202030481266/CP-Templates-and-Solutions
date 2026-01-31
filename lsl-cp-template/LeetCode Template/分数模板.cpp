#include <iostream>
#include <algorithm>

template <typename T>
T gcd(T a, T b) {
    while (b) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

template <typename T>
T lcm(T a, T b) {
    return (a / gcd(a, b)) * b;
}

template <typename T>
class Fraction {
public:

    T numerator_;
    T denominator_;

    Fraction(T numerator = 0, T denominator = 1) : numerator_(numerator), denominator_(denominator) {
        simplify();
    }

    Fraction operator+(const Fraction& other) const {
        T common_denominator = lcm(denominator_, other.denominator_);
        T new_numerator = (numerator_ * (common_denominator / denominator_)) + (other.numerator_ * (common_denominator / other.denominator_));
        return Fraction(new_numerator, common_denominator);
    }

    Fraction operator-(const Fraction& other) const {
        T common_denominator = lcm(denominator_, other.denominator_);
        T new_numerator = (numerator_ * (common_denominator / denominator_)) - (other.numerator_ * (common_denominator / other.denominator_));
        return Fraction(new_numerator, common_denominator);
    }

    Fraction operator*(const Fraction& other) const {
        T new_numerator = numerator_ * other.numerator_;
        T new_denominator = denominator_ * other.denominator_;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator/(const Fraction& other) const {
        T new_numerator = numerator_ * other.denominator_;
        T new_denominator = denominator_ * other.numerator_;
        return Fraction(new_numerator, new_denominator);
    }

    bool operator<(const Fraction& other) const {
        T common_denominator = lcm(denominator_, other.denominator_);
        T numerator1 = numerator_ * (common_denominator / denominator_);
        T numerator2 = other.numerator_ * (common_denominator / other.denominator_);
        return numerator1 < numerator2;
    }

    bool operator<=(const Fraction& other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>(const Fraction& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    bool operator==(const Fraction& other) const {
        return (numerator_ == other.numerator_) && (denominator_ == other.denominator_);
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    // 整型的写法
    bool operator>(const int& c) const {
        return (*this > Fraction<int>(c, 1));
    }

    bool operator==(const int& c) const {
        return (*this == Fraction<int>(c, 1));
    }

    bool operator!=(const int& c) const {
        return (*this != Fraction<int>(c, 1));
    }

    bool operator<(const int& c) const {
        return (*this < Fraction<int>(c, 1));
    }

    bool operator>=(const int& c) const {
        return (*this>c) || (*this==c);
    }

    bool operator<=(const int& c) const {
        return (*this<c) || (*this==c);
    }

    void simplify() {
        T common = gcd(numerator_, denominator_);
        numerator_ /= common;
        denominator_ /= common;
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    void print() const {
        std::cout << numerator_ << "/" << denominator_;
    }

    
};

// 使用哈希或者set使用的哈希函数结构体
struct FractionHash {
    std::size_t operator()(const Fraction<int>& fraction) const {
        // Use a simple hash function for Fraction objects
        return std::hash<int>()(fraction.numerator_) * 10000 + std::hash<int>()(fraction.denominator_);
    }
};

int main() {
    Fraction<int> a(1, 3);
    Fraction<int> b(2, 3);

    Fraction<int> result = a + b;
    std::cout << "a + b = ";
    result.print();
    std::cout << std::endl;

    result = a - b;
    std::cout << "a - b = ";
    result.print();
    std::cout << std::endl;

    result = a * b;
    std::cout << "a * b = ";
    result.print();
    std::cout << std::endl;

    result = a / b;
    std::cout << "a / b = ";
    result.print();
    std::cout << std::endl;

    return 0;
}
