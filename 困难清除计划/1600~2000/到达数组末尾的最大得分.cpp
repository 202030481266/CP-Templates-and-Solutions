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


class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size(), pre = 0;
        ll ans = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[pre]) {
                ans += 1ll * (i-pre) * nums[pre];
                pre = i;
            }
        }
        if (pre < n-1) ans += 1ll * (n-1-pre) * (nums[pre]);
        return ans;
    }
};
