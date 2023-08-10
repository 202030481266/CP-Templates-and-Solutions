/*
 vector<int> a{ 1, 2, 3, 4, 5 };
    do {
        vector<int> b(a);
        int cnt = 0;
        for (int& c : b) cout << c;
        cout << ' ';
        while (!is_sorted(b.begin(), b.end())) {
            int l, r;
            for (int i = 1; i < b.size(); ++i) {
                if (b[i] < b[i - 1]) l = i;
            }
            for (int i = l; i < b.size(); ++i) {
                if (b[i] < b[l - 1]) r = i;
                else break;
            }
            swap(b[l - 1], b[r]);
            reverse(b.begin() + l, b.end());
            ++cnt;
        }
        cout << cnt << '\n';
    } while (next_permutation(a.begin(), a.end()));
*/
// 我感觉就是和阶乘的顺序有关结果还真是！从全部的完全排序的个数看就知道了，一个是0，一个是阶乘数字-1
// 问题转换为等价的 数字顺序在阶乘的哪一个位置
typedef long long ll;
class Solution {
    static constexpr int mod = 1e9 + 7;
    ll fac[3005], ifac[3005], cnt[30];
public:
    long long quick_power(long long a, long long b) { 
        long long ans = 1 % mod;
        for(; b; b >>= 1) {
            if(b & 1) ans = ans * a % mod;
            a = a * a % mod;
        }
        return ans;
    }
    long long inv(long long x) {
        return quick_power(x, mod - 2) % mod;
    }
    long long binomial(int x, int y) {
        return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
    }
    int makeStringSorted(string s) {
        int n = s.size();
        ll ans = 0;
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = inv(fac[n]);
        for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
        for (char& ch : s) ++cnt[ch - 'a'];
        for (int i = 0; i < n; ++i) {
            int tmp = s[i] - 'a';
            for (int j = 0; j < tmp; ++j) {
                if (cnt[j] == 0) continue;
                ll c = fac[n - i - 1];
                --cnt[j];
                for (int k = 0; k < 26; ++k) c = c * ifac[cnt[k]] % mod;
                ans = (ans + c) % mod;
                ++cnt[j];
            }
            --cnt[tmp];
        }
        return ans;
    }
};
