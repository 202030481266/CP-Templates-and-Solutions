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
#define tiii tuple<int,int,int>
#define g0(t) get<0>(t)
#define g1(t) get<1>(t)
#define g2(t) get<2>(t)
#define mt3(a,b,c) make_tuple(a,b,c)


class Solution {
public:
    long long maximumAlternatingSubarraySum(vector<int>& nums) {
        int n = nums.size();
        ll ans = -INF,mx_1 = -INF, mx_0 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ll x = -INF, y = nums[i];
            x = max(mx_1 - nums[i], x); // 0
            y = max(mx_0 + nums[i], y); // 1
            ans = max(ans, max(x, y));
            mx_1 = y;
            mx_0 = x;
        }
        return ans;
    }
};
