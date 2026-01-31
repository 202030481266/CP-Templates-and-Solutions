#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] = (t[i] + value) % mod;
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res = (res + t[i]) % mod;
        return res;
    }

    // returns min(p | sum[0..p] >= sum)
    // requires non-negative tree values
    int lower_bound(T sum) {
        int highest_one_bit = 1;
        while (highest_one_bit << 1 <= t.size())
            highest_one_bit <<= 1;
        int pos = 0;
        // 使用倍增的方法来进行查找
        for (size_t blockSize = highest_one_bit; blockSize != 0; blockSize >>= 1) {
            int p = pos + blockSize - 1;
            if (p < t.size() && t[p] < sum) {
                sum -= t[p];
                pos += blockSize;
            }
        }
        return pos;
    }
};


class Solution {
public:
    int subarraysWithMoreZerosThanOnes(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n+1);
        // ones > r - l - ones
        // 2*cnt[r]-2*cnt[l] > r-l
        // 2*cnt[r]-r > 2*cnt[l]-l
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
        }
        int mn = INF, mx = -INF;
        for (int i = 1; i <= n; ++i) {
            if (2*sum[i]-i < mn) mn = 2*sum[i]-i;
            if (2*sum[i]-i > mx) mx = 2*sum[i]-i;
        }
        int offset = (mn < 0 ? -mn : 0); 
        fenwick<int> tree(mx+offset+1);
        tree.add(offset,1);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int tmp = 2 * sum[i] - i + offset;
            if (tmp > 0)
                ans = (ans + tree.sum(tmp-1)) % mod;
            tree.add(tmp, 1);
        }
        return ans;
    }
};

