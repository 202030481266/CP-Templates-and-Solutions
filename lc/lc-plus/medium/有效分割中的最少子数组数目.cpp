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
    int validSubarraySplit(vector<int>& nums) {
        // because we want the gcd(nums[i], nums[j]) is > 1
        int n = nums.size();
        vector<int> dp(n+1, INF);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (gcd(nums[i-1], nums[j-1]) > 1) 
                    dp[i] = min(dp[i], dp[j-1]+1);
            }
        }
        return dp[n] == INF ? -1 : dp[n];
    }
};

