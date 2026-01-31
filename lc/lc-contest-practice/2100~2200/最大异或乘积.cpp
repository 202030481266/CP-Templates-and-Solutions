using ll = long long;
const int mod = 1e9 + 7;
class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        // 贪心 ？
        ll mask = (1ll << n) - 1;
        ll A = a & mask, B = b & mask, C = A ^ B; 
        a -= A;
        b -= B;
        for (int i = n - 1; i >= 0; --i) { 
            // 总是分配给更加小的数字，因为乘法定理，和相同的情况下，两个数字的差越小，乘积越大
            if ((C >> i) & 1) {
                if (a > b) {
                    b |= (1ll << i);
                }
                else {
                    a |= (1ll << i);
                }
            }
            else {
                a |= (1ll << i);
                b |= (1ll << i);
            }
        }
        return ((a % mod) * (b % mod)) % mod;
    }
};