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

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


// 朴素方法
// 做一个等价转换就可以了，非常简单
// zero * a[r] - one * b[r] == zero * a[l] - one * b[l]

class Solution {
public:
    long long fixedRatio(string s, int zero, int one) {
        int n = s.size();
        ll a = 0, b = 0, ans = 0;
        unordered_map<ll, ll> cnt;
        cnt[0] = 1; 
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') ++a;
            else ++b;
            ans += cnt[zero*a - one*b];
            cnt[zero*a - one*b]++;
        }
        return ans;
    }
};