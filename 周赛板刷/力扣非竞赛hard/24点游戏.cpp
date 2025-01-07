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
struct FractionHash {
    std::size_t operator()(const Fraction<int>& fraction) const {
        // Use a simple hash function for Fraction objects
        return std::hash<int>()(fraction.numerator_) * 10000 + std::hash<int>()(fraction.denominator_);
    }
};
class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        int N = 16;
        unordered_set<Fraction<int>, FractionHash> h[N];
        for (int i = 0; i < 4; ++i) h[1 << i].insert(Fraction<int>(cards[i], 1));
        for (int s = 3; s < N; ++s) {
            // 枚举非空子集
            if (__builtin_popcount(s) == 1) continue;
            for (int t = (s - 1) & s; t; t = (t - 1) & s) {
                for (auto u : h[t])
                    for (auto v : h[s ^ t]) {
                        h[s].insert(u + v);
                        h[s].insert(u * v);
                        auto mx = (u > v ? u : v), mn = (u > v ? v : u);
                        if (mx - mn >= 0) h[s].insert(mx - mn);
                        if (mn != 0) h[s].insert(mx / mn);
                        if (mx != 0) h[s].insert(mn / mx);
                    }
            }
        }
        return h[N - 1].count(Fraction<int>(24, 1)) > 0;
    }
};