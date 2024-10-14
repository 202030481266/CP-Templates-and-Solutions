// 将 n 个不同的元素划分为m个非空集合的方法数量
// 可以解决任意的模数，算法复杂度O(n^2)
typedef long long ll;
typedef int itn;
const int N = 5007, mod = 1e9 + 7;
int n, m, k;
int S[N][N];
int main()
{
    scanf("%d%d", &n, &k);
    S[0][0] = 1;
    S[n][0] = 0;
    for(int i = 1; i <= n; ++ i) {
        for(int j = 1; j <= k; ++ j) {
            S[i][j] = (S[i- 1][j - 1] + 1ll * j * S[i - 1][j]) % mod;//公式中的 k 是当前的 k
        }
    }
    cout << S[n][k] << endl;
    return 0;
}


// NTT + 多项式，非常快，算法复杂度O(nlogn)，一般来说对于质数有要求，一般只用：998244353 还有1004535809和469762049等, 这三个数原根都是3
namespace OY {
    // Modular
    template <typename _ModType, _ModType _P>
    struct Modular {
        static constexpr _ModType mod() { return _P; }
        static constexpr _ModType mod(uint64_t __a) { return __a % _P; }
        static constexpr _ModType plus(_ModType __a, _ModType __b) {
            if (__a += __b; __a >= _P) __a -= _P;
            return __a;
        }
        static constexpr _ModType minus(_ModType __a, _ModType __b) {
            if (__a += _P - __b; __a >= _P) __a -= _P;
            return __a;
        }
        static constexpr _ModType multiply(uint64_t __a, uint64_t __b) {
            if constexpr (std::is_same_v<_ModType, uint64_t>)
                return multiply_ld(__a, __b);
            else
                return multiply_64(__a, __b);
        }
        static constexpr _ModType multiply_64(uint64_t __a, uint64_t __b) {
            // assert(__a * __b < 1ull << 64);
            return mod(__a * __b);
        }
        static constexpr _ModType multiply_128(uint64_t __a, uint64_t __b) { return __uint128_t(__a) * __b % _P; }
        static constexpr _ModType multiply_ld(uint64_t __a, uint64_t __b) {
            // assert(m_P < 1ull << 63 && __a < m_P && __b < m_P);
            int64_t res = __a * __b - uint64_t(1.L / _P * __a * __b) * _P;
            if (res < 0)
                res += _P;
            else if (res >= _P)
                res -= _P;
            return res;
        }
        static constexpr _ModType pow(uint64_t __a, uint64_t __n) {
            if constexpr (std::is_same_v<_ModType, uint64_t>)
                return pow_ld(__a, __n);
            else
                return pow_64(__a, __n);
        }
        static constexpr _ModType pow_64(uint64_t __a, uint64_t __n) {
            // assert(m_P < 1ull << 32);
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_64(res, b);
                b = multiply_64(b, b);
                __n >>= 1;
            }
            return res;
        }
        static constexpr _ModType pow_128(uint64_t __a, uint64_t __n) {
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_128(res, b);
                b = multiply_128(b, b);
                __n >>= 1;
            }
            return res;
        }
        static constexpr _ModType pow_ld(uint64_t __a, uint64_t __n) {
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_ld(res, b);
                b = multiply_ld(b, b);
                __n >>= 1;
            }
            return res;
        }
        template <typename _Tp>
        static constexpr _Tp divide(_Tp __a) { return __a / _P; }
        template <typename _Tp>
        static constexpr std::pair<_Tp, _Tp> divmod(_Tp __a) {
            _Tp quo = __a / _P, rem = __a - quo * _P;
            return {quo, rem};
        }
    };
    template <uint32_t _P>
    using Modular32 = Modular<uint32_t, _P>;
    template <uint64_t _P>
    using Modular64 = Modular<uint64_t, _P>;
    // StaticModInt32
    template <uint32_t P, bool IsPrime, typename = typename std::enable_if<(P > 1 && P < uint32_t(1) << 31)>::type>
    struct StaticModInt32 {
        using mint = StaticModInt32<P, IsPrime>;
        using mod_type = uint32_t;
        mod_type m_val;
        static mod_type _mul(mod_type a, mod_type b) { return uint64_t(a) * b % mod(); }
        StaticModInt32() : m_val{} {}
        template <typename Tp, typename std::enable_if<std::is_signed<Tp>::value>::type * = nullptr>
        StaticModInt32(Tp val) : m_val{} {
            auto x = val % int32_t(mod());
            if (x < 0) x += mod();
            m_val = x;
        }
        // template <typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value>::type * = nullptr>
        // StaticModInt32(Tp val) : m_val{val % mod()} {}
        static mint raw(mod_type val) {
            mint res;
            res.m_val = val;
            return res;
        }
        template <typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value>::type * = nullptr>
        StaticModInt32(Tp val) {
            Tp mod_val = static_cast<Tp>(mod());
            m_val = static_cast<mod_type>(val >= mod_val ? val % mod_val : val);
        }
        static constexpr mod_type mod() { return P; }
        mod_type val() const { return m_val; }
        mint pow(uint64_t n) const {
            mod_type res = 1, b = m_val;
            while (n) {
                if (n & 1) res = _mul(res, b);
                b = _mul(b, b), n >>= 1;
            }
            return raw(res);
        }
        mint inv() const {
            if constexpr (IsPrime)
                return inv_Fermat();
            else
                return inv_exgcd();
        }
        mint inv_exgcd() const {
            mod_type x = mod(), y = m_val, m0 = 0, m1 = 1;
            while (y) {
                mod_type z = x / y;
                x -= y * z, m0 -= m1 * z, std::swap(x, y), std::swap(m0, m1);
            }
            if (m0 >= mod()) m0 += mod() / x;
            return raw(m0);
        }
        mint inv_Fermat() const { return pow(mod() - 2); }
        mint &operator++() {
            if (++m_val == mod()) m_val = 0;
            return *this;
        }
        mint &operator--() {
            if (!m_val) m_val = mod();
            m_val--;
            return *this;
        }
        mint operator++(int) {
            mint old(*this);
            ++*this;
            return old;
        }
        mint operator--(int) {
            mint old(*this);
            --*this;
            return old;
        }
        mint &operator+=(const mint &rhs) {
            m_val += rhs.m_val;
            if (m_val >= mod()) m_val -= mod();
            return *this;
        }
        mint &operator-=(const mint &rhs) {
            m_val += mod() - rhs.m_val;
            if (m_val >= mod()) m_val -= mod();
            return *this;
        }
        mint &operator*=(const mint &rhs) {
            m_val = _mul(m_val, rhs.m_val);
            return *this;
        }
        mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }
        mint operator+() const { return *this; }
        mint operator-() const { return raw(m_val ? mod() - m_val : 0); }
        bool operator==(const mint &rhs) const { return m_val == rhs.m_val; }
        bool operator!=(const mint &rhs) const { return m_val != rhs.m_val; }
        bool operator<(const mint &rhs) const { return m_val < rhs.m_val; }
        bool operator>(const mint &rhs) const { return m_val > rhs.m_val; }
        bool operator<=(const mint &rhs) const { return m_val <= rhs.m_val; }
        bool operator>=(const mint &rhs) const { return m_val <= rhs.m_val; }
        template <typename Tp>
        explicit operator Tp() const { return Tp(m_val); }
        friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
        friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
        friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
        friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    };
    template <typename Istream, uint32_t P, bool IsPrime>
    Istream &operator>>(Istream &is, StaticModInt32<P, IsPrime> &x) { return is >> x.m_val; }
    template <typename Ostream, uint32_t P, bool IsPrime>
    Ostream &operator<<(Ostream &os, const StaticModInt32<P, IsPrime> &x) { return os << x.m_val; }
    using mint998244353 = OY::StaticModInt32<998244353, true>;
    using mint1000000007 = OY::StaticModInt32<1000000007, true>;
    // MTTPolynomial
    template <typename _Tp, uint32_t _MAXN = 1 << 22, typename _Fp = double, uint32_t _Split = 1 << 15>
    struct MTTPolynomial : std::vector<_Tp> {
        using poly = MTTPolynomial<_Tp, _MAXN, _Fp, _Split>;
        using std::vector<_Tp>::vector, std::vector<_Tp>::begin, std::vector<_Tp>::end, std::vector<_Tp>::rbegin, std::vector<_Tp>::rend, std::vector<_Tp>::size, std::vector<_Tp>::back, std::vector<_Tp>::empty, std::vector<_Tp>::clear, std::vector<_Tp>::pop_back, std::vector<_Tp>::resize, std::vector<_Tp>::push_back;
        static inline struct complex {
            _Fp x, y;
            complex() = default;
            complex(_Fp _val) : x(_val), y(0) {}
            complex(_Tp _val) : x(_val.val() / _Split), y(_val.val() % _Split) {}
            complex(_Fp _x, _Fp _y) : x(_x), y(_y) {}
            complex conj() const { return complex(x, -y); }
            complex operator-() const { return complex(-x, -y); }
            complex operator+(const complex &_other) const { return complex(x + _other.x, y + _other.y); }
            complex operator-(const complex &_other) const { return complex(x - _other.x, y - _other.y); }
            complex operator*(const complex &_other) const { return complex(x * _other.x - y * _other.y, x * _other.y + y * _other.x); }
            complex operator/(const complex &_other) const { return complex(x * _other.x + y * _other.y, y * _other.x - x * _other.y); }
            complex &operator+=(const complex &_other) { return *this = complex(x + _other.x, y + _other.y); }
            complex &operator-=(const complex &_other) { return *this = complex(x - _other.x, y - _other.y); }
            complex &operator*=(const complex &_other) { return *this = complex(x * _other.x - y * _other.y, x * _other.y + y * _other.x); }
            operator _Tp() const { return std::round(x) * _Tp(_Split) + std::round(y); }
        } s_dftRoots[_MAXN], s_dftBuffer[_MAXN * 2], s_treeBuffer[_MAXN * 2 * (std::__countr_zero(_MAXN))];
        static inline struct complex_pair {
            complex p, q;
            complex_pair() = default;
            complex_pair(_Fp _val) : p(_val), q(_val) {}
            complex_pair(const complex &_p, const complex &_q) : p(_p), q(_q) {}
            complex_pair(const complex &_a, const complex &_b, const complex &_c) : p(_c * _a), q(_c / _b) {}
            complex_pair operator+(const complex_pair &_other) const { return {p + _other.p, q + _other.q}; }
            complex_pair operator-(const complex_pair &_other) const { return {p - _other.p, q - _other.q}; }
            complex_pair operator*(const complex &_other) const { return {p * _other, q * _other}; }
            complex_pair &operator+=(const complex_pair &_other) { return *this = {p + _other.p, q + _other.q}; }
            complex_pair &operator-=(const complex_pair &_other) { return *this = {p - _other.p, q - _other.q}; }
            complex_pair &operator*=(_Fp _other) { return *this = {p * _other, q * _other}; }
            operator _Tp() const {
                complex x(p + q), y(p - q);
                _Tp u(_Split);
                return _Tp(std::round(x.x / 2) * u + std::round((x.y + y.y) / 2)) * u + std::round(-y.x / 2);
            }
            operator complex() const { return _Tp(*this); }
        } s_dftResultBuffer[_MAXN];
        static inline _Tp s_inverse[_MAXN + 1];
        static inline uint32_t s_dftBin[_MAXN * 2], s_dftSize = 1, s_inverseSize = 0;
        static inline poly s_treeSum;
        static void prepareDFT(uint32_t __length) {
            if (__length > s_dftSize) {
                if (s_dftSize == 1) s_dftRoots[s_dftSize++] = complex(1);
                for (; s_dftSize < __length; s_dftSize *= 2) {
                    const _Fp x(3.14159265358979323846L / s_dftSize);
                    const complex wn(std::cos(x), std::sin(x));
                    for (uint32_t i = s_dftSize; i < s_dftSize * 2; i += 2) {
                        s_dftRoots[i] = s_dftRoots[i / 2];
                        s_dftRoots[i + 1] = s_dftRoots[i / 2] * wn;
                    }
                }
            }
            if (__length > 1 && !s_dftBin[__length + 1])
                for (uint32_t i = 0; i < __length; i += 2) {
                    s_dftBin[__length + i] = s_dftBin[__length + i / 2] / 2;
                    s_dftBin[__length + i + 1] = s_dftBin[__length + i / 2] / 2 + __length / 2;
                }
        }
        template <typename _Iterator>
        static _Iterator _dft(_Iterator __iter, uint32_t __length) {
            for (uint32_t i = 0; i < __length; i++)
                if (uint32_t j = s_dftBin[__length + i]; i < j) std::swap(*(__iter + i), *(__iter + j));
            for (uint32_t h = 2; h <= __length; h *= 2)
                for (uint32_t j = 0; j < __length; j += h)
                    for (uint32_t k = j; k < j + h / 2; k++) {
                        auto x(*(__iter + k)), y(*(__iter + (k + h / 2)) * s_dftRoots[h / 2 + k - j]);
                        *(__iter + k) += y;
                        *(__iter + (k + h / 2)) = x - y;
                    }
            return __iter;
        }
        template <typename _Iterator>
        static _Iterator dft(_Iterator __iter, uint32_t __length) { return prepareDFT(__length), _dft(__iter, __length); }
        template <typename _Iterator, typename _Iterator2>
        static _Iterator dft(_Iterator __iter, uint32_t __dftLength, _Iterator2 __source, uint32_t __sourceLength) { return dft(std::fill_n(std::copy_n(__source, __sourceLength, __iter), __dftLength - __sourceLength, 0) - __dftLength, __dftLength); }
        template <typename _Iterator>
        static _Iterator idft(_Iterator __iter, uint32_t __length) {
            _dft(__iter, __length);
            std::reverse(__iter + 1, __iter + __length);
            const _Fp inv(1 / _Fp(__length));
            for (uint32_t i = 0; i < __length; i++) *(__iter + i) *= inv;
            return __iter;
        }
        template <typename _Iterator, typename _Iterator2, typename _Iterator3>
        static _Iterator _transform(_Iterator __iter1, _Iterator2 __iter2, _Iterator3 __iter3, uint32_t __length) {
            for (uint32_t i = 0, j = 0; i < __length; i++, j = j ? j - 1 : __length - 1) {
                (*(__iter1 + i)).p = *(__iter3 + i) * *(__iter2 + i);
                (*(__iter1 + i)).q = *(__iter3 + i) / *(__iter2 + (i ? __length - i : 0));
            }
            return __iter1;
        }
        static void prepareInverse(uint32_t __length) {
            if (s_inverseSize >= __length) return;
            if (!s_inverseSize) s_inverse[0] = s_inverse[++s_inverseSize] = _Tp(1);
            const auto P(_Tp::mod());
            for (uint32_t i = s_inverseSize + 1; i <= __length; i++) {
                auto q = P / i, r = P - q * i;
                s_inverse[i] = s_inverse[r] * _Tp(P - q);
            }
            s_inverseSize = __length;
        }
        template <typename _Iterator>
        static void derivate(_Iterator __iter, uint32_t __length) {
            for (uint32_t i = 0; i + 1 < __length; i++) __iter[i] = __iter[i + 1] * (i + 1);
            __iter[__length - 1] = 0;
        }
        template <typename _Iterator>
        static void integrate(_Iterator __iter, uint32_t __length) {
            if (!__length) return;
            prepareInverse(__length);
            for (uint32_t i = __length; i; i--) *(__iter + i) = *(__iter + (i - 1)) * s_inverse[i];
            __iter[0] = 0;
        }
        static poly product(const poly &__a, const poly &__b, uint32_t __length) {
            if (__a.empty() || __b.empty()) return poly();
            idft(_transform(s_dftResultBuffer, dft(s_dftBuffer, __length, __a.begin(), std::min<uint32_t>(__length, __a.size())), dft(s_dftBuffer + __length, __length, __b.begin(), std::min<uint32_t>(__length, __b.size())), __length), __length);
            return poly(s_dftResultBuffer, s_dftResultBuffer + __length);
        }
        poly &shrink() {
            while (size() && !back()) pop_back();
            return *this;
        }
        poly &reverse() {
            std::reverse(begin(), end());
            return *this;
        }
        poly &sizeTo(uint32_t __size) {
            resize(__size);
            return *this;
        }
        poly &derivate() {
            derivate(begin(), size());
            shrink();
            return *this;
        }
        poly &integrate() {
            push_back(0);
            integrate(begin(), size() - 1);
            shrink();
            return *this;
        }
        _Tp at(uint32_t __i) const { return __i < size() ? (*this)[__i] : 0; }
        poly &operator+=(const poly &__other) {
            if (size() < __other.size()) resize(__other.size());
            std::transform(begin(), begin() + __other.size(), __other.begin(), begin(), std::plus<_Tp>());
            return shrink();
        }
        poly &operator-=(const poly &__other) {
            if (size() < __other.size()) resize(__other.size());
            std::transform(begin(), begin() + __other.size(), __other.begin(), begin(), std::minus<_Tp>());
            return shrink();
        }
        poly &operator*=(_Tp __other) {
            if (!__other)
                clear();
            else
                for (auto &a : *this) a *= __other;
            return *this;
        }
        poly &operator*=(const poly &__other) { return (*this = product(*this, __other, std::__bit_ceil(size() + __other.size() - 1))).shrink(); }
        poly &operator/=(_Tp __other) {
            for (auto &a : *this) a /= __other;
            return *this;
        }
        poly operator+() const { return *this; }
        poly operator-() const {
            poly res(*this);
            std::transform(res.begin(), res.end(), res.begin(), std::negate<_Tp>());
            return res;
        }
        friend poly operator+(const poly &__a, const poly &__b) {
            poly res(__a);
            res += __b;
            return res;
        }
        friend poly operator-(const poly &__a, const poly &__b) {
            poly res(__a);
            res -= __b;
            return res;
        }
        friend poly operator*(const poly &__a, _Tp __b) {
            poly res(__a);
            res *= __b;
            return res;
        }
        friend poly operator*(const poly &__a, const poly &__b) {
            poly res(product(__a, __b, std::__bit_ceil(__a.size() + __b.size() - 1)));
            res.shrink();
            return res;
        }
        friend poly operator/(const poly &__a, _Tp __b) {
            poly res(__a);
            res /= __b;
            return res;
        }
        template <typename _Istream>
        friend _Istream &operator>>(_Istream &__is, poly &__self) {
            for (auto &a : __self) __is >> a;
            return __is;
        }
        template <typename _Ostream>
        friend _Ostream &operator<<(_Ostream &__os, const poly &__self) {
            for (auto &a : __self) __os << a << ' ';
            return __os;
        }
        _Tp calc(_Tp __x) const {
            _Tp res = 0;
            for (uint32_t i = size() - 1; ~i; i--) res = res * __x + (*this)[i];
            return res;
        }
        poly ChirpZ(_Tp __x, uint32_t __n) const {
            if (empty()) return poly(__n, 0);
            const uint32_t length = std::__bit_ceil(size() + __n - 1);
            const _Tp inv(__x.inv());
            _Tp cur(1), pow(1);
            for (uint32_t i = 0; i < size() + __n - 1; i++, cur *= pow, pow *= __x) s_dftBuffer[i] = cur;
            cur = _Tp(1), pow = _Tp(1);
            for (uint32_t i = size() - 1; ~i; i--, cur *= pow, pow *= inv) s_dftBuffer[length + i] = (*this)[size() - 1 - i] * cur;
            idft(_transform(s_dftResultBuffer, dft(std::fill_n(s_dftBuffer + size() + __n - 1, length - size() - __n + 1, _Fp(0)) - length, length), dft(std::fill_n(s_dftBuffer + length + size(), length - size(), _Fp(0)) - length, length), length), length);
            poly res(s_dftResultBuffer + size() - 1, s_dftResultBuffer + size() - 1 + __n);
            cur = _Tp(1).inv(), pow = 1;
            for (auto &a : res) a *= cur, cur *= pow, pow *= inv;
            return res;
        }
        poly inv() const {
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R];
            complex f[Block * R * 2], g[Block * R * 2], h[Block * 2];
            res[0] = (*this)[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(f, block * 2, begin(), block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, begin() + block * k, block * k < size() ? std::min<uint32_t>(size() - block * k, block) : 0);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(s_dftResultBuffer, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++) {
                        complex *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2;
                        for (uint32_t i = 0; i < block * 2; i += 2) s_dftResultBuffer[i] -= {*(it1 + i), *(it1 + (i ? block * 2 - i : 0)), *(it2 + i) + *(it3 + i)}, s_dftResultBuffer[i + 1] -= {*(it1 + (i + 1)), *(it1 + (block * 2 - i - 1)), *(it2 + (i + 1)) - *(it3 + (i + 1))};
                    }
                    std::copy_n(idft(_transform(s_dftResultBuffer, dft(h, block * 2, idft(s_dftResultBuffer, block * 2), block), g, block * 2), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        poly sqrt(_Tp __a0 = 1) const {
            if (empty()) return poly();
            static constexpr uint32_t R = 16;
            const _Tp inv(_Tp(2).inv());
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R];
            complex f[Block * 2], g[Block * R * 2], h[Block * 2];
            res[0] = __a0;
            auto dfs = [&](auto self, uint32_t n) {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(f, block * 2, poly(res, res + block).inv().begin(), block);
                std::fill_n(g, block * R * 2, 0);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(s_dftResultBuffer, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++) {
                        complex *it1 = g + block * j * 2, *it2 = g + block * (k - j) * 2, *it3 = g + block * (k - j - 1) * 2;
                        for (uint32_t i = 0; i < block * 2; i += 2) s_dftResultBuffer[i] += {*(it1 + i), *(it1 + (i ? block * 2 - i : 0)), *(it2 + i) + *(it3 + i)}, s_dftResultBuffer[i + 1] += {*(it1 + (i + 1)), *(it1 + (block * 2 - i - 1)), *(it2 + (i + 1)) - *(it3 + (i + 1))};
                    }
                    idft(s_dftResultBuffer, block * 2);
                    for (uint32_t i = 0; i < block; i++) h[i] = at(block * k + i) - _Tp(s_dftResultBuffer[i]);
                    idft(_transform(s_dftResultBuffer, dft(std::fill_n(h + block, block, _Fp(0)) - block * 2, block * 2), f, block * 2), block * 2);
                    for (uint32_t i = 0; i < block; i++) res[block * k + i] = _Tp(s_dftResultBuffer[i]) * inv;
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        std::pair<poly, poly> divmod(const poly &__other) const {
            if (size() < __other.size()) return {poly(), *this};
            std::pair<poly, poly> res;
            res.first = div(__other, size() - __other.size() + 1);
            res.second = *this - res.first * __other;
            return res;
        }
        poly div(const poly &__other, uint32_t __length = -1) const {
            __length = std::min<uint32_t>(__length, size());
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((__length - 1) / R + 1);
            _Tp res[Block * R], a[Block * R], b[Block * R];
            complex f[Block * R * 2], g[Block * R * 2], h[Block * 2], bi[Block * 2];
            poly binv(poly(__other).reverse().sizeTo(Block).inv());
            std::fill(std::copy_n(rbegin(), __length, a), a + Block * R, 0);
            std::fill(std::copy_n(__other.rbegin(), std::min<uint32_t>(__length, __other.size()), b), b + Block * R, 0);
            res[0] = a[0] * b[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(bi, block * 2, binv.begin(), block);
                dft(f, block * 2, b, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, b + block * k, block);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(s_dftResultBuffer, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++) {
                        complex *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2;
                        for (uint32_t i = 0; i < block * 2; i += 2) s_dftResultBuffer[i] += {*(it1 + i), *(it1 + (i ? block * 2 - i : 0)), *(it2 + i) + *(it3 + i)}, s_dftResultBuffer[i + 1] += {*(it1 + (i + 1)), *(it1 + (block * 2 - i - 1)), *(it2 + (i + 1)) - *(it3 + (i + 1))};
                    }
                    idft(s_dftResultBuffer, block * 2);
                    for (uint32_t i = 0; i < block; i++) h[i] = _Tp(a[block * k + i]) - _Tp(s_dftResultBuffer[i]);
                    std::copy_n(idft(_transform(s_dftResultBuffer, dft(std::fill_n(h + block, block, 0) - block * 2, block * 2), bi, block * 2), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, __length);
            return poly(res, res + __length).reverse();
        }
        poly mod(const poly &__other) const { return divmod(__other).second; }
        poly logarithm() const {
            prepareInverse(size());
            poly f(*this);
            for (uint32_t i = 0; i < size(); i++) f[i] *= i;
            (f = f.reverse().div(poly(*this).reverse())).reverse();
            for (uint32_t i = 1; i < size(); i++) f[i] *= s_inverse[i];
            return f;
        }
        poly exponent() const {
            if (empty()) return poly{_Tp(1)};
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R], a[Block * R];
            complex f[Block * R * 2], g[Block * R * 2], h[Block * 2], bi[Block * 2];
            std::fill(std::copy_n(begin(), size(), a), a + Block * R, 0);
            for (uint32_t i = 0; i < size(); i++) a[i] *= i;
            res[0] = 1;
            prepareInverse(Block * (R + 1));
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(bi, block * 2, poly(res, res + block).inv().begin(), block);
                dft(f, block * 2, a, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, a + block * k, block);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(s_dftResultBuffer, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++) {
                        complex *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2;
                        for (uint32_t i = 0; i < block * 2; i += 2) s_dftResultBuffer[i] += {*(it1 + i), *(it1 + (i ? block * 2 - i : 0)), *(it2 + i) + *(it3 + i)}, s_dftResultBuffer[i + 1] += {*(it1 + (i + 1)), *(it1 + (block * 2 - i - 1)), *(it2 + (i + 1)) - *(it3 + (i + 1))};
                    }
                    idft(_transform(s_dftResultBuffer, dft(h, block * 2, idft(s_dftResultBuffer, block * 2), block), bi, block * 2), block * 2);
                    for (uint32_t i = 0; i < block; i++) h[i] = _Tp(s_dftResultBuffer[i]) * s_inverse[block * k + i];
                    std::copy_n(idft(_transform(s_dftResultBuffer, dft(std::fill_n(h + block, block, _Fp(0)) - block * 2, block * 2), g, block * 2), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        static poly _simplePow(const poly &__a, _Tp __n) { return (__a.logarithm() * __n).exponent(); }
        template <typename _Tp2>
        poly pow(_Tp __n1, _Tp2 __n2, uint64_t __nAbs = UINT_MAX) const {
            const uint64_t zero = std::find_if(begin(), end(), [](const _Tp &x) { return x.val() != 0; }) - begin();
            if (zero && __nAbs >= (size() + zero - 1) / zero) return poly();
            if (!__n1) return poly{(*this)[zero].pow(__n2.val())};
            uint32_t rest = size() - zero * __nAbs;
            poly a(begin() + zero, begin() + zero + std::min<uint32_t>(rest, size() - zero)), res(size(), _Tp(0));
            const _Tp a0(a[0]);
            (a = _simplePow(a *= a0.inv(), __n1)) *= a0.pow(__n2.val());
            std::copy_n(a.begin(), a.size(), res.begin() + (size() - rest));
            return res;
        }
        static void _initTree(const poly &__xs, uint32_t __length) {
            complex *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2);
            for (uint32_t i = 0; i < __length; i++) {
                *it++ = _Tp(1), *it++ = -__xs.at(i);
                dft(it - 2, 2);
            }
            for (uint32_t h = 2; h < __length; h *= 2) {
                complex *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2 / h);
                for (uint32_t i = 0; i < __length; i += h, it += h * 2) {
                    std::fill_n(std::copy_n(idft(_transform(s_dftResultBuffer, it + __length * 2, it + __length * 2 + h, h), h), h, it), h, _Fp(0));
                    *(it + h) = _Tp(*it) - 1, *it = _Tp(1);
                    dft(it, h * 2);
                }
            }
            std::copy_n(idft(_transform(s_dftResultBuffer, s_treeBuffer, s_treeBuffer + __length, __length), __length), __length, s_treeSum.sizeTo(0).sizeTo(__length * 2).begin());
            s_treeSum[__length] = _Tp(s_treeSum[0]) - _Tp(1);
            s_treeSum[0] = _Tp(1);
        }
        static poly _calcTree(const poly &__f, uint32_t __resLength) {
            const uint32_t length = s_treeSum.size() / 2;
            _Tp res[length];
            std::copy_n(__f.div(s_treeSum.reverse()).reverse().begin(), __f.size(), std::fill_n(res, length - __f.size(), 0));
            for (uint32_t h = length / 2; h; h >>= 1) {
                complex *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h);
                for (_Tp *it = res, *end = res + __resLength; it < end; it += h * 2, it2 += h * 4) std::copy_n(s_dftResultBuffer + h, h, std::copy_n(idft(_transform(idft(_transform(s_dftResultBuffer, s_dftBuffer, dft(std::copy_n(it2 + h * 2, h * 2, std::copy_n(it2, h * 2, s_dftBuffer)), h * 2, it, h * 2), h * 2), h * 2) + h * 2, s_dftBuffer + h * 2, s_dftBuffer + h * 4, h * 2), h * 2) + h, h, it));
            }
            return poly(res, res + __resLength);
        }
        static poly fromPoints(const poly &__xs, const poly &__ys) {
            if (__xs.size() <= 1) return __ys;
            const uint32_t length = std::__bit_ceil(__xs.size());
            _initTree(__xs, length);
            _Tp res[length];
            std::fill(std::copy_n(_calcTree(poly(s_treeSum).sizeTo(__xs.size() + 1).reverse().derivate(), __xs.size()).begin(), __xs.size(), res), res + length, 0);
            for (uint32_t i = 0; i < __ys.size(); i++) res[i] = __ys[i] / res[i];
            for (uint32_t h = 1; h < length; h *= 2) {
                _Tp *it = res, *end = res + __xs.size();
                complex *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h);
                for (; it < end; it += h * 2, it2 += h * 4) {
                    dft(dft(s_dftBuffer, h * 2, it, h) + h * 2, h * 2, it + h, h);
                    for (uint32_t i = 0; i < h * 2; i += 2) {
                        s_dftResultBuffer[i] = {s_dftBuffer[i], s_dftBuffer[i ? h * 2 - i : 0], *(it2 + (h * 2 + i))};
                        s_dftResultBuffer[i] += {s_dftBuffer[h * 2 + i], s_dftBuffer[i ? h * 4 - i : h * 2], *(it2 + i)};
                        s_dftResultBuffer[i + 1] = {s_dftBuffer[i + 1], s_dftBuffer[h * 2 - i - 1], *(it2 + (h * 2 + i + 1))};
                        s_dftResultBuffer[i + 1] += {s_dftBuffer[h * 2 + i + 1], s_dftBuffer[h * 4 - i - 1], *(it2 + (i + 1))};
                    }
                    std::copy_n(idft(s_dftResultBuffer, h * 2), h * 2, it);
                }
            }
            poly _res(res, res + __xs.size());
            _res.reverse();
            return _res;
        }
        poly calc(const poly &__xs) const {
            _initTree(__xs, std::__bit_ceil(std::max<uint32_t>(__xs.size(), size())));
            return _calcTree(*this, __xs.size());
        }
    };
    // NTTPolynomial
    template <typename _Tp, uint32_t _MAXN = 1 << 22>
    struct NTTPolynomial : std::vector<_Tp> {
        using poly = NTTPolynomial<_Tp, _MAXN>;
        using std::vector<_Tp>::vector, std::vector<_Tp>::begin, std::vector<_Tp>::end, std::vector<_Tp>::rbegin, std::vector<_Tp>::rend, std::vector<_Tp>::size, std::vector<_Tp>::back, std::vector<_Tp>::empty, std::vector<_Tp>::clear, std::vector<_Tp>::pop_back, std::vector<_Tp>::resize, std::vector<_Tp>::push_back;
        static inline _Tp s_dftRoots[_MAXN], s_dftBuffer[_MAXN * 2], s_inverse[_MAXN + 1], s_treeBuffer[_MAXN * 2 * (std::__countr_zero(_MAXN))], s_primitiveRoot;
        static inline uint32_t s_dftBin[_MAXN * 2], s_dftSize = 1, s_inverseSize = 0;
        static inline poly s_treeSum;
        static void prepareDFT(uint32_t __length) {
            if (__length > s_dftSize) {
                if (s_dftSize == 1) s_dftRoots[s_dftSize++] = _Tp(1);
                for (; s_dftSize < __length; s_dftSize *= 2) {
                    const _Tp wn(s_primitiveRoot.pow((_Tp::mod() - 1) / (s_dftSize * 2)));
                    for (uint32_t i = s_dftSize; i < s_dftSize * 2; i += 2) {
                        s_dftRoots[i] = s_dftRoots[i / 2];
                        s_dftRoots[i + 1] = s_dftRoots[i / 2] * wn;
                    }
                }
            }
            if (__length > 1 && !s_dftBin[__length + 1])
                for (uint32_t i = 0; i < __length; i += 2) {
                    s_dftBin[__length + i] = s_dftBin[__length + i / 2] / 2;
                    s_dftBin[__length + i + 1] = s_dftBin[__length + i / 2] / 2 + __length / 2;
                }
        }
        template <typename _Iterator>
        static _Iterator _dft(_Iterator __iter, uint32_t __length) {
            for (uint32_t i = 0; i < __length; i++)
                if (uint32_t j = s_dftBin[__length + i]; i < j) std::swap(*(__iter + i), *(__iter + j));
            for (uint32_t h = 2; h <= __length; h *= 2)
                for (uint32_t j = 0; j < __length; j += h)
                    for (uint32_t k = j; k < j + h / 2; k++) {
                        _Tp x(*(__iter + k)), y(*(__iter + (k + h / 2)) * s_dftRoots[h / 2 + k - j]);
                        *(__iter + k) += y;
                        *(__iter + (k + h / 2)) = x - y;
                    }
            return __iter;
        }
        template <typename _Iterator>
        static _Iterator _setHighZero(_Iterator __iter, uint32_t __length) { return std::fill_n(__iter + __length / 2, __length / 2, 0) - __length; }
        template <typename _Iterator>
        static _Iterator dft(_Iterator __iter, uint32_t __length) { return prepareDFT(__length), _dft(__iter, __length); }
        template <typename _Iterator, typename _Iterator2>
        static _Iterator dft(_Iterator __iter, uint32_t __dftLength, _Iterator2 __source, uint32_t __sourceLength) { return dft(std::fill_n(std::copy_n(__source, __sourceLength, __iter), __dftLength - __sourceLength, 0) - __dftLength, __dftLength); }
        template <typename _Iterator>
        static _Iterator idft(_Iterator __iter, uint32_t __length) {
            _dft(__iter, __length);
            std::reverse(__iter + 1, __iter + __length);
            const _Tp inv(_Tp(__length).inv());
            for (uint32_t i = 0; i < __length; i++) *(__iter + i) *= inv;
            return __iter;
        }
        template <typename _Iterator, typename _Iterator2, typename _Operation>
        static _Iterator _transform(_Iterator __iter1, _Iterator2 __iter2, uint32_t __length, _Operation __op = _Operation()) { return std::transform(__iter1, __iter1 + __length, __iter2, __iter1, __op) - __length; }
        static void prepareInverse(uint32_t __length) {
            if (s_inverseSize >= __length) return;
            if (!s_inverseSize) s_inverse[0] = s_inverse[++s_inverseSize] = _Tp(1);
            const auto P(_Tp::mod());
            for (uint32_t i = s_inverseSize + 1; i <= __length; i++) {
                auto q = P / i, r = P - q * i;
                s_inverse[i] = s_inverse[r] * _Tp(P - q);
            }
            s_inverseSize = __length;
        }
        template <typename _Iterator>
        static void derivate(_Iterator __iter, uint32_t __length) {
            if (!__length) return;
            for (uint32_t i = 0; i + 1 < __length; i++) *(__iter + i) = *(__iter + (i + 1)) * (i + 1);
            *(__iter + (__length - 1)) = _Tp(0);
        }
        template <typename _Iterator>
        static void integrate(_Iterator __iter, uint32_t __length) {
            if (!__length) return;
            prepareInverse(__length);
            for (uint32_t i = __length; i; i--) *(__iter + i) = *(__iter + (i - 1)) * s_inverse[i];
            __iter[0] = 0;
        }
        static poly product(const poly &__a, const poly &__b, uint32_t __length) {
            if (__a.empty() || __b.empty()) return poly();
            idft(_transform(dft(s_dftBuffer, __length, __a.begin(), std::min<uint32_t>(__length, __a.size())), dft(s_dftBuffer + __length, __length, __b.begin(), std::min<uint32_t>(__length, __b.size())), __length, std::multiplies<_Tp>()), __length);
            return poly(s_dftBuffer, s_dftBuffer + __length);
        }
        poly &shrink() {
            while (size() && !back()) pop_back();
            return *this;
        }
        poly &reverse() {
            std::reverse(begin(), end());
            return *this;
        }
        poly &sizeTo(uint32_t __size) {
            resize(__size);
            return *this;
        }
        poly &derivate() {
            derivate(begin(), size());
            shrink();
            return *this;
        }
        poly &integrate() {
            push_back(0);
            integrate(begin(), size() - 1);
            shrink();
            return *this;
        }
        _Tp at(uint32_t __i) const { return __i < size() ? (*this)[__i] : 0; }
        poly &operator+=(const poly &__other) {
            _transform(sizeTo(std::max<uint32_t>(size(), __other.size())).begin(), __other.begin(), __other.size(), std::plus<_Tp>());
            return shrink();
        }
        poly &operator-=(const poly &__other) {
            _transform(sizeTo(std::max<uint32_t>(size(), __other.size())).begin(), __other.begin(), __other.size(), std::minus<_Tp>());
            return shrink();
        }
        poly &operator*=(_Tp __other) {
            if (!__other)
                clear();
            else
                for (auto &a : *this) a *= __other;
            return *this;
        }
        poly &operator*=(const poly &__other) { return (*this = product(*this, __other, std::__bit_ceil(size() + __other.size() - 1))).shrink(); }
        poly &operator/=(_Tp __other) {
            for (auto &a : *this) a /= __other;
            return *this;
        }
        poly operator+() const { return *this; }
        poly operator-() const {
            poly res(*this);
            std::transform(res.begin(), res.end(), res.begin(), std::negate<_Tp>());
            return res;
        }
        friend poly operator+(const poly &__a, const poly &__b) {
            poly res(__a);
            res += __b;
            return res;
        }
        friend poly operator-(const poly &__a, const poly &__b) {
            poly res(__a);
            res -= __b;
            return res;
        }
        friend poly operator*(const poly &__a, _Tp __b) {
            poly res(__a);
            res *= __b;
            return res;
        }
        friend poly operator*(const poly &__a, const poly &__b) {
            poly res(product(__a, __b, std::__bit_ceil(__a.size() + __b.size() - 1)));
            res.shrink();
            return res;
        }
        friend poly operator/(const poly &__a, _Tp __b) {
            poly res(__a);
            res /= __b;
            return res;
        }
        template <typename _Istream>
        friend _Istream &operator>>(_Istream &__is, poly &__self) {
            for (auto &a : __self) __is >> a;
            return __is;
        }
        template <typename _Ostream>
        friend _Ostream &operator<<(_Ostream &__os, const poly &__self) {
            for (auto &a : __self) __os << a << ' ';
            return __os;
        }
        _Tp calc(_Tp __x) const {
            _Tp res = 0;
            for (uint32_t i = size() - 1; ~i; i--) res = res * __x + (*this)[i];
            return res;
        }
        poly ChirpZ(_Tp __x, uint32_t __n) const {
            if (empty()) return poly(__n, 0);
            const uint32_t length = std::__bit_ceil(size() + __n - 1);
            const _Tp inv(__x.inv());
            _Tp cur(1), pow(1);
            for (uint32_t i = 0; i < size() + __n - 1; i++, cur *= pow, pow *= __x) s_dftBuffer[i] = cur;
            cur = _Tp(1), pow = _Tp(1);
            for (uint32_t i = size() - 1; ~i; i--, cur *= pow, pow *= inv) s_dftBuffer[length + i] = (*this)[size() - 1 - i] * cur;
            idft(_transform(dft(std::fill_n(s_dftBuffer + size() + __n - 1, length - size() - __n + 1, 0) - length, length), dft(std::fill_n(s_dftBuffer + length + size(), length - size(), 0) - length, length), length, std::multiplies<_Tp>()), length);
            cur = _Tp(1).inv(), pow = _Tp(1);
            for (uint32_t i = size() - 1, j = 0; j < __n; i++, j++, cur *= pow, pow *= inv) s_dftBuffer[i] *= cur;
            return poly(s_dftBuffer + size() - 1, s_dftBuffer + size() - 1 + __n);
        }
        poly inv() const {
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp f[Block * R * 2], g[Block * R * 2], res[Block * (R + 1)];
            res[0] = (*this)[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(f, block * 2, begin(), block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, begin() + block * k, block * k < size() ? std::min<uint32_t>(size() - block * k, block) : 0);
                    dft(std::copy_n(std::fill_n(res + block * k, block * 2, 0) - block * 3, block * 2, g + block * (k - 1) * 2) - block * 2, block * 2);
                    for (uint32_t j = 0; j < k; j++)
                        for (_Tp *it = res + block * k, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = res + block * (k + 2); it != end;) *it++ -= *it1++ * (*it2++ + *it3++), *it++ -= *it1++ * (*it2++ - *it3++);
                    idft(_transform(dft(_setHighZero(idft(res + block * k, block * 2), block * 2), block * 2), g, block * 2, std::multiplies<_Tp>()), block * 2);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        poly sqrt(_Tp __a0 = 1) const {
            if (empty()) return poly();
            static constexpr uint32_t R = 16;
            const _Tp inv2(_Tp::mod() / 2 + 1);
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp g[Block * R * 2], h[Block * 2], res[Block * (R + 1)];
            res[0] = __a0;
            auto dfs = [&](auto self, uint32_t n) {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(h, block * 2, poly(res, res + block).inv().begin(), block);
                std::fill_n(g, block * R * 2, 0);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(std::copy_n(std::fill_n(res + block * k, block * 2, 0) - block * 3, block * 2, g + block * (k - 1) * 2) - block * 2, block * 2);
                    for (uint32_t j = 0; j < k; j++)
                        for (_Tp *it = res + block * k, *it1 = g + block * j * 2, *it2 = g + block * (k - j) * 2, *it3 = g + block * (k - j - 1) * 2, *end = res + block * (k + 2); it != end;) *it++ -= *it1++ * (*it2++ + *it3++), *it++ -= *it1++ * (*it2++ - *it3++);
                    _setHighZero(idft(res + block * k, block * 2), block * 2);
                    for (uint32_t i = block * k, iend = block * (k + 1); i < iend; i++) res[i] += at(i);
                    idft(_transform(dft(res + block * k, block * 2), h, block * 2, std::multiplies<_Tp>()), block * 2);
                    for (uint32_t i = block * k, iend = block * (k + 1); i < iend; i++) res[i] *= inv2;
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        std::pair<poly, poly> divmod(const poly &__other) const {
            if (size() < __other.size()) return {poly(), *this};
            std::pair<poly, poly> res;
            res.first = div(__other, size() - __other.size() + 1);
            res.second = *this - res.first * __other;
            return res;
        }
        poly div(const poly &__other, uint32_t __length = -1) const {
            __length = std::min<uint32_t>(__length, size());
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((__length - 1) / R + 1);
            _Tp f[Block * R * 2], g[Block * R * 2], h[Block * 2], a[Block * R], b[Block * R], res[Block * (R + 1)];
            poly binv(poly(__other).reverse().sizeTo(Block).inv());
            std::fill(std::copy_n(rbegin(), __length, a), a + Block * R, 0);
            std::fill(std::copy_n(__other.rbegin(), std::min<uint32_t>(__length, __other.size()), b), b + Block * R, 0);
            res[0] = a[0] * b[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(h, block * 2, binv.begin(), block);
                dft(f, block * 2, b, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, b + block * k, block);
                    dft(std::copy_n(std::fill_n(res + block * k, block * 2, 0) - block * 3, block * 2, g + block * (k - 1) * 2) - block * 2, block * 2);
                    for (uint32_t j = 0; j < k; j++)
                        for (_Tp *it = res + block * k, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = res + block * (k + 2); it != end;) *it++ -= *it1++ * (*it2++ + *it3++), *it++ -= *it1++ * (*it2++ - *it3++);
                    idft(_transform(dft(_transform(_setHighZero(idft(res + block * k, block * 2), block * 2), a + block * k, block, std::plus<_Tp>()), block * 2), h, block * 2, std::multiplies<_Tp>()), block * 2);
                }
            };
            dfs(dfs, __length);
            return poly(res, res + __length).reverse();
        }
        poly mod(const poly &__other) const { return divmod(__other).second; }
        poly logarithm() const {
            prepareInverse(size());
            poly f(*this);
            for (uint32_t i = 0; i < size(); i++) f[i] *= i;
            (f = f.reverse().div(poly(*this).reverse())).reverse();
            for (uint32_t i = 1; i < size(); i++) f[i] *= s_inverse[i];
            return f;
        }
        poly exponent() const {
            if (empty()) return poly{_Tp(1)};
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp f[Block * R * 2], g[Block * R * 2], h[Block * 2], a[Block * R], res[Block * (R + 1)];
            std::fill(std::copy_n(begin(), size(), a), a + Block * R, 0);
            for (uint32_t i = 0; i < size(); i++) a[i] *= i;
            res[0] = 1;
            prepareInverse(Block * (R + 1));
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(h, block * 2, poly(res, res + block).inv().begin(), block);
                dft(f, block * 2, a, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, a + block * k, block);
                    dft(std::copy_n(std::fill_n(res + block * k, block * 2, 0) - block * 3, block * 2, g + block * (k - 1) * 2) - block * 2, block * 2);
                    for (uint32_t j = 0; j < k; j++)
                        for (_Tp *it = res + block * k, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = res + block * (k + 2); it != end;) *it++ += *it1++ * (*it2++ + *it3++), *it++ += *it1++ * (*it2++ - *it3++);
                    idft(_transform(dft(_transform(_setHighZero(idft(_transform(dft(_setHighZero(idft(res + block * k, block * 2), block * 2), block * 2), h, block * 2, std::multiplies<_Tp>()), block * 2), block * 2), s_inverse + block * k, block, std::multiplies<_Tp>()), block * 2), g, block * 2, std::multiplies<_Tp>()), block * 2);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        static poly _simplePow(const poly &__a, _Tp __n) { return (__a.logarithm() * __n).exponent(); }
        template <typename _Fp>
        poly pow(_Tp __n1, _Fp __n2, uint64_t __nAbs = UINT64_MAX) const {
            const uint64_t zero = std::find_if(begin(), end(), [](const _Tp &x) { return x.val() != 0; }) - begin();
            if (zero && __nAbs >= (size() + zero - 1) / zero) return poly();
            if (!__n1) return poly{(*this)[zero].pow(__n2.val())};
            uint32_t rest = size() - zero * __nAbs;
            poly a(begin() + zero, begin() + zero + std::min<uint32_t>(rest, size() - zero)), res(size(), _Tp(0));
            const _Tp a0(a[0]);
            (a = _simplePow(a *= a0.inv(), __n1)) *= a0.pow(__n2.val());
            std::copy_n(a.begin(), a.size(), res.begin() + (size() - rest));
            return res;
        }
        static void _initTree(const poly &__xs, uint32_t __length) {
            _Tp *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2);
            for (uint32_t i = 0; i < __length; i++) *it++ = _Tp(1), *it++ = -__xs.at(i);
            for (uint32_t h = 2; h < __length; h *= 2) {
                _Tp *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2 / h);
                for (uint32_t i = 0; i < __length; i += h, it += h * 2) {
                    idft(std::fill_n(std::transform(dft(it + __length * 2, h), it + __length * 2 + h, dft(it + __length * 2 + h, h), it, std::multiplies<_Tp>()), h, 0) - h * 2, h);
                    *(it + h) = *it - 1, *it = 1;
                }
            }
            idft(std::transform(dft(s_treeBuffer, __length), s_treeBuffer + __length, dft(s_treeBuffer + __length, __length), s_treeSum.sizeTo(__length * 2).begin(), std::multiplies<_Tp>()) - __length, __length);
            s_treeSum[__length] = s_treeSum[0] - _Tp(1);
            s_treeSum[0] = _Tp(1);
        }
        static poly _calcTree(const poly &__f, uint32_t __resLength) {
            const uint32_t length = std::__bit_ceil(std::max<uint32_t>(__f.size(), s_treeSum.size() / 2));
            poly res(length);
            std::copy_n(__f.div(s_treeSum.reverse()).reverse().begin(), __f.size(), res.begin() + length - __f.size());
            for (uint32_t h = length / 2; h; h /= 2)
                for (_Tp *it = res.data(), *end = res.data() + __resLength, *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h); it < end; it += h * 2, it2 += h * 4) std::copy_n(s_dftBuffer + h, h, std::copy_n(idft(_transform(idft(_transform(std::copy_n(it2 + h * 2, h * 2, std::copy_n(it2, h * 2, s_dftBuffer)) - h * 4, dft(it, h * 2), h * 2, std::multiplies<_Tp>()), h * 2) + h * 2, it, h * 2, std::multiplies<_Tp>()), h * 2) + h, h, it));
            res.sizeTo(__resLength);
            return res;
        }
        static poly fromPoints(const poly &__xs, const poly &__ys) {
            if (__xs.size() <= 1) return __ys;
            const uint32_t length = std::__bit_ceil(__xs.size());
            _initTree(__xs, length);
            poly res(_calcTree(poly(s_treeSum).sizeTo(__xs.size() + 1).reverse().derivate(), __xs.size()).sizeTo(length));
            for (uint32_t i = 0; i < __ys.size(); i++) res[i] = __ys[i] / res[i];
            for (uint32_t h = 1; h < length; h *= 2)
                for (_Tp *it = res.data(), *end = res.data() + __xs.size(), *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h); it < end; it += h * 2, it2 += h * 4) {
                    dft(dft(s_dftBuffer, h * 2, it, h) + h * 2, h * 2, it + h, h);
                    for (uint32_t i = 0; i < h * 2; i++) *(it + i) = s_dftBuffer[i] * *(it2 + (h * 2 + i)) + s_dftBuffer[h * 2 + i] * *(it2 + i);
                    idft(it, h * 2);
                }
            res.sizeTo(__xs.size()).reverse();
            return res;
        }
        poly calc(const poly &__xs) const {
            _initTree(__xs, std::__bit_ceil(std::max<uint32_t>(__xs.size(), size())));
            return _calcTree(*this, __xs.size());
        }
    };
    // NTTPolynomial_ex
    template <typename _Tp, uint32_t _MAXN = 1 << 22, uint32_t _P1 = 1107296257, uint32_t _R1 = 10, uint32_t _P2 = 1711276033, uint32_t _R2 = 29, uint32_t _P3 = 1811939329, uint32_t _R3 = 13>
    struct NTTPolynomial_ex : std::vector<_Tp> {
        using poly = NTTPolynomial_ex<_Tp, _MAXN, _P1, _R1, _P2, _R2, _P3, _R3>;
        using std::vector<_Tp>::vector, std::vector<_Tp>::begin, std::vector<_Tp>::end, std::vector<_Tp>::rbegin, std::vector<_Tp>::rend, std::vector<_Tp>::size, std::vector<_Tp>::back, std::vector<_Tp>::empty, std::vector<_Tp>::clear, std::vector<_Tp>::pop_back, std::vector<_Tp>::resize, std::vector<_Tp>::push_back;
        static inline struct triple {
            static constexpr uint32_t inv_1_2 = Modular32<_P2>::pow(_P1, _P2 - 2), inv_12_3 = Modular32<_P3>::pow(Modular32<_P3>::multiply(_P1, _P2), _P3 - 2);
            static constexpr uint64_t P12 = uint64_t(_P1) * _P2;
            uint32_t x, y, z;
            triple() = default;
            triple(uint32_t _val) : x(_val), y(_val), z(_val) {}
            triple(_Tp _val) : x(_val.val()), y(_val.val()), z(_val.val()) {}
            triple(uint32_t _x, uint32_t _y, uint32_t _z) : x(_x), y(_y), z(_z) {}
            static triple root(uint32_t __n) { return triple(Modular32<_P1>::pow(_R1, (_P1 - 1) / __n), Modular32<_P2>::pow(_R2, (_P2 - 1) / __n), Modular32<_P3>::pow(_R3, (_P3 - 1) / __n)); }
            static triple inv(uint32_t __x) { return triple(Modular32<_P1>::pow(__x, _P1 - 2), Modular32<_P2>::pow(__x, _P2 - 2), Modular32<_P3>::pow(__x, _P3 - 2)); }
            triple operator+(const triple &_other) const { return triple(Modular32<_P1>::plus(x, _other.x), Modular32<_P2>::plus(y, _other.y), Modular32<_P3>::plus(z, _other.z)); }
            triple operator-(const triple &_other) const { return triple(Modular32<_P1>::minus(x, _other.x), Modular32<_P2>::minus(y, _other.y), Modular32<_P3>::minus(z, _other.z)); }
            triple operator*(const triple &_other) const { return triple(Modular32<_P1>::multiply(x, _other.x), Modular32<_P2>::multiply(y, _other.y), Modular32<_P3>::multiply(z, _other.z)); }
            triple &operator+=(const triple &_other) { return *this = operator+(_other); }
            triple &operator-=(const triple &_other) { return *this = operator-(_other); }
            triple &operator*=(const triple &_other) { return *this = operator*(_other); }
            triple &reduce() {
                uint64_t X = uint64_t(Modular32<_P2>::multiply(Modular32<_P2>::minus(y, x), inv_1_2)) * _P1 + x;
                _Tp val(Modular32<_P3>::multiply(Modular32<_P3>::minus(z, Modular32<_P3>::mod(X)), inv_12_3) * _Tp(P12) + X);
                return *this = triple(val.val(), val.val(), val.val());
            }
            operator _Tp() const { return _Tp(x); }
        } s_dftRoots[_MAXN], s_dftBuffer[_MAXN * 2], s_treeBuffer[_MAXN * 2 * (std::__countr_zero(_MAXN))];
        static inline _Tp s_inverse[_MAXN + 1];
        static inline uint32_t s_dftBin[_MAXN * 2], s_dftSize = 1, s_inverseSize = 0;
        static inline poly s_treeSum;
        static void prepareDFT(uint32_t __length) {
            if (__length > s_dftSize) {
                if (s_dftSize == 1) s_dftRoots[s_dftSize++] = triple(1);
                for (; s_dftSize < __length; s_dftSize *= 2) {
                    const triple wn(triple::root(s_dftSize * 2));
                    for (uint32_t i = s_dftSize; i < s_dftSize * 2; i += 2) {
                        s_dftRoots[i] = s_dftRoots[i / 2];
                        s_dftRoots[i + 1] = s_dftRoots[i / 2] * wn;
                    }
                }
            }
            if (__length > 1 && !s_dftBin[__length + 1])
                for (uint32_t i = 0; i < __length; i += 2) {
                    s_dftBin[__length + i] = s_dftBin[__length + i / 2] / 2;
                    s_dftBin[__length + i + 1] = s_dftBin[__length + i / 2] / 2 + __length / 2;
                }
        }
        template <typename _Iterator>
        static _Iterator _dft(_Iterator __iter, uint32_t __length) {
            for (uint32_t i = 0; i < __length; i++)
                if (uint32_t j = s_dftBin[__length + i]; i < j) std::swap(*(__iter + i), *(__iter + j));
            for (uint32_t h = 2; h <= __length; h *= 2)
                for (uint32_t j = 0; j < __length; j += h)
                    for (uint32_t k = j; k < j + h / 2; k++) {
                        triple x(*(__iter + k)), y(*(__iter + (k + h / 2)) * s_dftRoots[h / 2 + k - j]);
                        *(__iter + k) += y;
                        *(__iter + (k + h / 2)) = x - y;
                    }
            return __iter;
        }
        template <typename _Iterator>
        static _Iterator _setHighZero(_Iterator __iter, uint32_t __length) { return std::fill_n(__iter + __length / 2, __length / 2, 0) - __length; }
        template <typename _Iterator>
        static _Iterator dft(_Iterator __iter, uint32_t __length) { return prepareDFT(__length), _dft(__iter, __length); }
        template <typename _Iterator, typename _Iterator2>
        static _Iterator dft(_Iterator __iter, uint32_t __dftLength, _Iterator2 __source, uint32_t __sourceLength) { return dft(std::fill_n(std::copy_n(__source, __sourceLength, __iter), __dftLength - __sourceLength, 0) - __dftLength, __dftLength); }
        template <typename _Iterator>
        static _Iterator idft(_Iterator __iter, uint32_t __length) {
            _dft(__iter, __length);
            std::reverse(__iter + 1, __iter + __length);
            const triple inv(triple::inv(__length));
            for (uint32_t i = 0; i < __length; i++) (*(__iter + i) *= inv).reduce();
            return __iter;
        }
        template <typename _Iterator, typename _Iterator2, typename _Operation>
        static _Iterator _transform(_Iterator __iter1, _Iterator2 __iter2, uint32_t __length, _Operation __op = _Operation()) { return std::transform(__iter1, __iter1 + __length, __iter2, __iter1, __op) - __length; }
        static void prepareInverse(uint32_t __length) {
            if (s_inverseSize >= __length) return;
            if (!s_inverseSize) s_inverse[0] = s_inverse[++s_inverseSize] = _Tp(1);
            const auto P(_Tp::mod());
            for (uint32_t i = s_inverseSize + 1; i <= __length; i++) {
                auto q = P / i, r = P - q * i;
                s_inverse[i] = s_inverse[r] * _Tp(P - q);
            }
            s_inverseSize = __length;
        }
        template <typename _Iterator>
        static void derivate(_Iterator __iter, uint32_t __length) {
            if (!__length) return;
            for (uint32_t i = 0; i + 1 < __length; i++) *(__iter + i) = *(__iter + (i + 1)) * (i + 1);
            *(__iter + (__length - 1)) = _Tp(0);
        }
        template <typename _Iterator>
        static void integrate(_Iterator __iter, uint32_t __length) {
            if (!__length) return;
            prepareInverse(__length);
            for (uint32_t i = __length; i; i--) *(__iter + i) = *(__iter + (i - 1)) * s_inverse[i];
            __iter[0] = 0;
        }
        static poly product(const poly &__a, const poly &__b, uint32_t __length) {
            if (__a.empty() || __b.empty()) return poly();
            idft(_transform(dft(s_dftBuffer, __length, __a.begin(), std::min<uint32_t>(__length, __a.size())), dft(s_dftBuffer + __length, __length, __b.begin(), std::min<uint32_t>(__length, __b.size())), __length, std::multiplies<triple>()), __length);
            return poly(s_dftBuffer, s_dftBuffer + __length);
        }
        poly &shrink() {
            while (size() && !back()) pop_back();
            return *this;
        }
        poly &reverse() {
            std::reverse(begin(), end());
            return *this;
        }
        poly &sizeTo(uint32_t __size) {
            resize(__size);
            return *this;
        }
        poly &derivate() {
            derivate(begin(), size());
            shrink();
            return *this;
        }
        poly &integrate() {
            push_back(0);
            integrate(begin(), size() - 1);
            shrink();
            return *this;
        }
        _Tp at(uint32_t __i) const { return __i < size() ? (*this)[__i] : 0; }
        poly &operator+=(const poly &__other) {
            _transform(sizeTo(std::max<uint32_t>(size(), __other.size())).begin(), __other.begin(), __other.size(), std::plus<_Tp>());
            return shrink();
        }
        poly &operator-=(const poly &__other) {
            _transform(sizeTo(std::max<uint32_t>(size(), __other.size())).begin(), __other.begin(), __other.size(), std::minus<_Tp>());
            return shrink();
        }
        poly &operator*=(_Tp __other) {
            if (!__other)
                clear();
            else
                for (auto &a : *this) a *= __other;
            return *this;
        }
        poly &operator*=(const poly &__other) { return (*this = product(*this, __other, std::__bit_ceil(size() + __other.size() - 1))).shrink(); }
        poly &operator/=(_Tp __other) {
            for (auto &a : *this) a /= __other;
            return *this;
        }
        poly operator+() const { return *this; }
        poly operator-() const {
            poly res(*this);
            std::transform(res.begin(), res.end(), res.begin(), std::negate<_Tp>());
            return res;
        }
        friend poly operator+(const poly &__a, const poly &__b) {
            poly res(__a);
            res += __b;
            return res;
        }
        friend poly operator-(const poly &__a, const poly &__b) {
            poly res(__a);
            res -= __b;
            return res;
        }
        friend poly operator*(const poly &__a, _Tp __b) {
            poly res(__a);
            res *= __b;
            return res;
        }
        friend poly operator*(const poly &__a, const poly &__b) {
            poly res(product(__a, __b, std::__bit_ceil(__a.size() + __b.size() - 1)));
            res.shrink();
            return res;
        }
        friend poly operator/(const poly &__a, _Tp __b) {
            poly res(__a);
            res /= __b;
            return res;
        }
        template <typename _Istream>
        friend _Istream &operator>>(_Istream &__is, poly &__self) {
            for (auto &a : __self) __is >> a;
            return __is;
        }
        template <typename _Ostream>
        friend _Ostream &operator<<(_Ostream &__os, const poly &__self) {
            for (auto &a : __self) __os << a << ' ';
            return __os;
        }
        _Tp calc(_Tp __x) const {
            _Tp res = 0;
            for (uint32_t i = size() - 1; ~i; i--) res = res * __x + (*this)[i];
            return res;
        }
        poly ChirpZ(_Tp __x, uint32_t __n) const {
            if (empty()) return poly(__n, 0);
            const uint32_t length = std::__bit_ceil(size() + __n - 1);
            const _Tp inv(__x.inv());
            _Tp cur(1), pow(1);
            for (uint32_t i = 0; i < size() + __n - 1; i++, cur *= pow, pow *= __x) s_dftBuffer[i] = cur;
            cur = _Tp(1), pow = _Tp(1);
            for (uint32_t i = size() - 1; ~i; i--, cur *= pow, pow *= inv) s_dftBuffer[length + i] = (*this)[size() - 1 - i] * cur;
            idft(_transform(dft(std::fill_n(s_dftBuffer + size() + __n - 1, length - size() - __n + 1, 0) - length, length), dft(std::fill_n(s_dftBuffer + length + size(), length - size(), 0) - length, length), length, std::multiplies<triple>()), length);
            poly res(s_dftBuffer + size() - 1, s_dftBuffer + size() - 1 + __n);
            cur = _Tp(1).inv(), pow = _Tp(1);
            for (auto &a : res) a *= cur, cur *= pow, pow *= inv;
            return res;
        }
        poly inv() const {
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R];
            triple f[Block * R * 2], g[Block * R * 2], h[Block * 2];
            res[0] = (*this)[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(f, block * 2, begin(), block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, begin() + block * k, block * k < size() ? std::min<uint32_t>(size() - block * k, block) : 0);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(h, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++)
                        for (triple *it = h, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = h + block * 2; it != end;) *it++ += *it1++ * (*it2++ + *it3++), *it++ += *it1++ * (*it2++ - *it3++);
                    idft(h, block * 2);
                    for (uint32_t i = 0; i < block * 2; i++) h[i] = -_Tp(h[i]);
                    std::copy_n(idft(_transform(dft(_setHighZero(h, block * 2), block * 2), g, block * 2, std::multiplies<triple>()), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        poly sqrt(_Tp __a0 = 1) const {
            if (empty()) return poly();
            static constexpr uint32_t R = 16;
            const _Tp inv(_Tp(2).inv());
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R];
            triple f[Block * 2], g[Block * R * 2], h[Block * 2];
            res[0] = __a0;
            auto dfs = [&](auto self, uint32_t n) {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(f, block * 2, poly(res, res + block).inv().begin(), block);
                std::fill_n(g, block * R * 2, 0);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(h, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++)
                        for (triple *it = h, *it1 = g + block * j * 2, *it2 = g + block * (k - j) * 2, *it3 = g + block * (k - j - 1) * 2, *end = h + block * 2; it != end;) *it++ += *it1++ * (*it2++ + *it3++), *it++ += *it1++ * (*it2++ - *it3++);
                    _setHighZero(idft(h, block * 2), block * 2);
                    for (uint32_t i = 0; i < block; i++) h[i] = at(block * k + i) - _Tp(h[i]);
                    idft(_transform(dft(h, block * 2), f, block * 2, std::multiplies<triple>()), block * 2);
                    for (uint32_t i = 0; i < block; i++) res[block * k + i] = _Tp(h[i]) * inv;
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        std::pair<poly, poly> divmod(const poly &__other) const {
            if (size() < __other.size()) return {poly(), *this};
            std::pair<poly, poly> res;
            res.first = div(__other, size() - __other.size() + 1);
            res.second = *this - res.first * __other;
            return res;
        }
        poly div(const poly &__other, uint32_t __length = -1) const {
            __length = std::min<uint32_t>(__length, size());
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((__length - 1) / R + 1);
            _Tp res[Block * R], a[Block * R], b[Block * R];
            triple f[Block * R * 2], g[Block * R * 2], h[Block * 2], bi[Block * 2];
            poly binv(poly(__other).reverse().sizeTo(Block).inv());
            std::fill(std::copy_n(rbegin(), __length, a), a + Block * R, 0);
            std::fill(std::copy_n(__other.rbegin(), std::min<uint32_t>(__length, __other.size()), b), b + Block * R, 0);
            res[0] = a[0] * b[0].inv();
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(bi, block * 2, binv.begin(), block);
                dft(f, block * 2, b, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, b + block * k, block);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(h, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++)
                        for (triple *it = h, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = h + block * 2; it != end;) *it++ += *it1++ * (*it2++ + *it3++), *it++ += *it1++ * (*it2++ - *it3++);
                    _setHighZero(idft(h, block * 2), block * 2);
                    for (uint32_t i = 0; i < block; i++) h[i] = _Tp(a[block * k + i]) - _Tp(h[i]);
                    std::copy_n(idft(_transform(dft(h, block * 2), bi, block * 2, std::multiplies<triple>()), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, __length);
            return poly(res, res + __length).reverse();
        }
        poly mod(const poly &__other) const { return divmod(__other).second; }
        poly logarithm() const {
            prepareInverse(size());
            poly f(*this);
            for (uint32_t i = 0; i < size(); i++) f[i] *= i;
            (f = f.reverse().div(poly(*this).reverse())).reverse();
            for (uint32_t i = 1; i < size(); i++) f[i] *= s_inverse[i];
            return f;
        }
        poly exponent() const {
            if (empty()) return poly{_Tp(1)};
            static constexpr uint32_t R = 16;
            const uint32_t Block = std::__bit_ceil((size() - 1) / R + 1);
            _Tp res[Block * R], a[Block * R];
            triple f[Block * R * 2], g[Block * R * 2], h[Block * 2], bi[Block * 2];
            std::fill(std::copy_n(begin(), size(), a), a + Block * R, 0);
            for (uint32_t i = 0; i < size(); i++) a[i] *= i;
            res[0] = 1;
            prepareInverse(Block * (R + 1));
            auto dfs = [&](auto self, uint32_t n) -> void {
                if (n == 1) return;
                const uint32_t block = std::__bit_ceil((n - 1) / R + 1);
                self(self, block);
                dft(bi, block * 2, poly(res, res + block).inv().begin(), block);
                dft(f, block * 2, a, block);
                for (uint32_t k = 1; block * k < n; k++) {
                    dft(f + block * k * 2, block * 2, a + block * k, block);
                    dft(g + block * (k - 1) * 2, block * 2, res + block * (k - 1), block);
                    std::fill_n(h, block * 2, 0);
                    for (uint32_t j = 0; j < k; j++)
                        for (triple *it = h, *it1 = g + block * j * 2, *it2 = f + block * (k - j) * 2, *it3 = f + block * (k - j - 1) * 2, *end = h + block * 2; it != end;) *it++ += *it1++ * (*it2++ + *it3++), *it++ += *it1++ * (*it2++ - *it3++);
                    std::copy_n(idft(_transform(dft(_transform(_setHighZero(idft(_transform(dft(_setHighZero(idft(h, block * 2), block * 2), block * 2), bi, block * 2, std::multiplies<triple>()), block * 2), block * 2), s_inverse + block * k, block, std::multiplies<_Tp>()), block * 2), g, block * 2, std::multiplies<triple>()), block * 2), block, res + block * k);
                }
            };
            dfs(dfs, size());
            return poly(res, res + size());
        }
        static poly _simplePow(const poly &__a, _Tp __n) { return (__a.logarithm() * __n).exponent(); }
        template <typename _Fp>
        poly pow(_Tp __n1, _Fp __n2, uint64_t __nAbs = UINT_MAX) const {
            const uint64_t zero = std::find_if(begin(), end(), [](const _Tp &x) { return x.val() != 0; }) - begin();
            if (zero && __nAbs >= (size() + zero - 1) / zero) return poly();
            if (!__n1) return poly{(*this)[zero].pow(__n2.val())};
            uint32_t rest = size() - zero * __nAbs;
            poly a(begin() + zero, begin() + zero + std::min<uint32_t>(rest, size() - zero)), res(size(), _Tp(0));
            const _Tp a0(a[0]);
            (a = _simplePow(a *= a0.inv(), __n1)) *= a0.pow(__n2.val());
            std::copy_n(a.begin(), a.size(), res.begin() + (size() - rest));
            return res;
        }
        static void _initTree(const poly &__xs, uint32_t __length) {
            triple *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2);
            for (uint32_t i = 0; i < __length; i++) *it++ = triple(1), *it++ = triple(-__xs.at(i));
            for (uint32_t h = 2; h < __length; h *= 2) {
                triple *it = s_treeBuffer + __length * 2 * std::__countr_zero(__length / 2 / h);
                for (uint32_t i = 0; i < __length; i += h, it += h * 2) {
                    idft(std::fill_n(std::transform(dft(it + __length * 2, h), it + __length * 2 + h, dft(it + __length * 2 + h, h), it, std::multiplies<triple>()), h, 0) - h * 2, h);
                    *(it + h) = *it - 1, *it = 1;
                }
            }
            std::copy_n(idft(std::transform(dft(s_treeBuffer, __length), s_treeBuffer + __length, dft(s_treeBuffer + __length, __length), s_dftBuffer, std::multiplies<triple>()) - __length, __length), __length, s_treeSum.sizeTo(0).sizeTo(__length * 2).begin());
            s_treeSum[__length] = s_treeSum[0] - _Tp(1);
            s_treeSum[0] = _Tp(1);
        }
        static poly _calcTree(const poly &__f, uint32_t __resLength) {
            const uint32_t length = s_treeSum.size() / 2;
            triple res[length];
            std::copy_n(__f.div(s_treeSum.reverse()).reverse().begin(), __f.size(), std::fill_n(res, length - __f.size(), 0));
            for (uint32_t h = length / 2; h; h /= 2)
                for (triple *it = res, *end = res + __resLength, *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h); it < end; it += h * 2, it2 += h * 4) std::copy_n(s_dftBuffer + h, h, std::copy_n(idft(_transform(idft(_transform(std::copy_n(it2 + h * 2, h * 2, std::copy_n(it2, h * 2, s_dftBuffer)) - h * 4, dft(it, h * 2), h * 2, std::multiplies<triple>()), h * 2) + h * 2, it, h * 2, std::multiplies<triple>()), h * 2) + h, h, it));
            return poly(res, res + __resLength);
        }
        static poly fromPoints(const poly &__xs, const poly &__ys) {
            if (__xs.size() <= 1) return __ys;
            const uint32_t length = std::__bit_ceil(__xs.size());
            _initTree(__xs, length);
            triple res[length];
            std::fill(std::copy_n(_calcTree(poly(s_treeSum).sizeTo(__xs.size() + 1).reverse().derivate(), __xs.size()).begin(), __xs.size(), res), res + length, 0);
            for (uint32_t i = 0; i < __ys.size(); i++) res[i] = __ys[i] / _Tp(res[i]);
            for (uint32_t h = 1; h < length; h *= 2)
                for (triple *it = res, *end = res + __xs.size(), *it2 = s_treeBuffer + length * 2 * std::__countr_zero(length / 2 / h); it < end; it += h * 2, it2 += h * 4) {
                    dft(dft(s_dftBuffer, h * 2, it, h) + h * 2, h * 2, it + h, h);
                    for (uint32_t i = 0; i < h * 2; i++) *(it + i) = s_dftBuffer[i] * *(it2 + (h * 2 + i)) + s_dftBuffer[h * 2 + i] * *(it2 + i);
                    idft(it, h * 2);
                }
            poly _res(res, res + __xs.size());
            _res.reverse();
            return _res;
        }
        poly calc(const poly &__xs) const {
            _initTree(__xs, std::__bit_ceil(std::max<uint32_t>(__xs.size(), size())));
            return _calcTree(*this, __xs.size());
        }
    };
    // StirlingNumber
    template <typename _Poly>
    struct StirlingNumber {
        using _Tp = typename _Poly::value_type;
        std::vector<std::array<uint32_t, 2>> m_factors;
        std::vector<_Tp> m_factorial, m_factorialInv;
        StirlingNumber(uint32_t __n) : m_factors(__n + 1), m_factorial(__n + 1, _Tp(1)), m_factorialInv(__n + 1) {
            const uint32_t sqrt = std::sqrt(__n);
            for (uint32_t i = 4, j = 2; i <= __n; i += 2, j++) m_factors[i] = {2, j};
            for (uint32_t i = 3; i <= sqrt; i += 2)
                if (!m_factors[i][0])
                    for (uint32_t j = i * i, k = i; j <= __n; j += i * 2, k += 2) m_factors[j] = {i, k};
            for (uint32_t i = 1; i <= __n; i++) m_factorial[i] = m_factorial[i - 1] * _Tp(i);
            m_factorialInv.back() = m_factorial.back().inv();
            for (uint32_t i = __n - 1; ~i; i--) m_factorialInv[i] = m_factorialInv[i + 1] * _Tp(i + 1);
        }
        std::vector<_Poly> getFirstStirlingTable(uint32_t __n) const {
            std::vector<_Poly> res(__n + 1);
            for (uint32_t i = 0; i <= __n; i++) {
                res[i].reserve(i + 1);
                for (uint32_t j = 0; j < i; j++) res[i].push_back(j ? res[i - 1][j - 1] + _Tp(i - 1) * res[i - 1][j] : _Tp(0));
                res[i].emplace_back(1);
            }
            return res;
        }
        std::vector<_Poly> getSecondStirlingTable(uint32_t __n) const {
            std::vector<_Poly> res(__n + 1);
            for (uint32_t i = 0; i <= __n; i++) {
                res[i].reserve(i + 1);
                for (uint32_t j = 0; j < i; j++) res[i].push_back(j ? res[i - 1][j - 1] + j * res[i - 1][j] : _Tp(0));
                res[i].emplace_back(1);
            }
            return res;
        }
        _Poly getFirstStirlingRow(uint32_t __row) const {
            _Poly res{_Tp(0), _Tp(1)};
            if (!__row) {
                res.pop_back();
                return res;
            }
            for (uint32_t i = std::__countr_zero(std::__bit_floor(__row)) - 1; ~i; i--) {
                _Poly a(res), b(res.size());
                for (uint32_t j = 0; j < b.size(); j++) b[j] = j ? b[j - 1] * _Tp(a.size() - 1) : 1;
                for (uint32_t j = 0; j < b.size(); j++) b[j] *= m_factorialInv[j];
                for (uint32_t j = 0; j < a.size(); j++) a[j] *= m_factorial[j];
                (a.reverse() *= b).sizeTo(b.size()).reverse();
                for (uint32_t j = 0; j < a.size(); j++) a[j] *= m_factorialInv[j];
                if (__row >> i & 1)
                    for (uint32_t j = a.sizeTo(a.size() + 1).size() - 1, k = b.size() * 2 - 2; ~j; j--) (a[j] *= k) += a.at(j - 1);
                res *= a;
            }
            return res;
        }
        _Poly getSecondStirlingRow(uint32_t __row) const {
            _Tp pow[__row + 1];
            pow[0] = _Tp(0), pow[1] = _Tp(1);
            for (uint32_t i = 2; i <= __row; i++)
                if (auto &[a, b] = m_factors[i]; a)
                    pow[i] = pow[a] * pow[b];
                else
                    pow[i] = _Tp(i).pow(__row);
            _Poly a(__row + 1), b(__row + 1);
            for (uint32_t i = 0; i <= __row; i++) a[i] = pow[i] * m_factorialInv[i], b[i] = i % 2 ? -m_factorialInv[i] : m_factorialInv[i];
            (a *= b).sizeTo(__row + 1);
            return a;
        }
        _Poly getFirstStirlingCol(uint32_t __col, uint32_t __maxRow) const {
            if (!__col) {
                _Poly res(__maxRow + 1);
                res[0] = _Tp(1);
                return res;
            }
            if (__col == 1) {
                _Poly res(__maxRow + 1);
                res[__col] = _Tp(1);
                for (uint32_t i = __col + 1; i < res.size(); i++) res[i] = res[i - 1] * _Tp(i - __col);
                return res;
            }
            if (__maxRow < __col) return _Poly(__maxRow + 1);
            _Poly a(__maxRow);
            for (uint32_t i = 0; i < __maxRow; i++) a[i] = m_factorial[i] * m_factorialInv[i + 1];
            _Poly b(_Poly::_simplePow(a, _Tp(__col))), res(__maxRow + 1);
            for (uint32_t i = __col; i <= __maxRow; i++) res[i] = b[i - __col] * m_factorial[i] * m_factorialInv[__col];
            return res;
        }
        _Poly getSecondStirlingCol(uint32_t __col, uint32_t __maxRow) const {
            if (!__col) {
                _Poly res(__maxRow + 1);
                res[0] = _Tp(1);
                return res;
            }
            if (__col == 1) return _Poly(__maxRow + 1, _Tp(1));
            if (__maxRow < __col) return _Poly(__maxRow + 1);
            _Poly a(m_factorialInv.begin() + 1, m_factorialInv.begin() + (__maxRow - __col + 2)), b(_Poly::_simplePow(a, _Tp(__col))), res(__maxRow + 1);
            for (uint32_t i = __col; i <= __maxRow; i++) res[i] = b[i - __col] * m_factorial[i] * m_factorialInv[__col];
            return res;
        }
    };
}
using poly = OY::NTTPolynomial<OY::mint998244353, 1 << 18>;
int main() {
    // 只要用到 ntt 记得设置原根
    poly::s_primitiveRoot = 3;

    OY::StirlingNumber<poly> sn(100);

    // 第一类斯特林数完整打表
    // auto sn1 = sn.getFirstStirlingTable(6);
    // for (int i = 0; i <= 6; i++)
    //     cout << sn1[i] << endl;

    // 第一类斯特林数打出第 4 行
    // auto sn1_row = sn.getFirstStirlingRow(4);
    // cout << sn1_row << endl;

    // 第一类斯特林数打出第 4 列，最大行数指定为 6
    // auto sn1_col = sn.getFirstStirlingCol(4, 6);
    // cout << sn1_col << endl;

    // 第二类斯特林数完整打表
    // auto sn2 = sn.getSecondStirlingTable(6);
    // for (int i = 0; i <= 6; i++)
    //     cout << sn2[i] << endl;

    // 第二类斯特林数打出第 4 行
    auto sn2_row = sn.getSecondStirlingRow(3);
    cout << sn2_row << endl;

    // 第二类斯特林数打出第 4 列，最大行数指定为 6
    // auto sn2_col = sn.getSecondStirlingCol(4, 6);
    // cout << sn2_col << endl;
}