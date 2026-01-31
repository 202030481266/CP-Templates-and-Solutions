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

vi split(const std::string &s, char delim) {
    std::vector<int> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        result.push_back(item.length());
    }
    return result;
}


class Solution {
public:
    int minimumCost(string sentence, int k) {
        vi words = split(sentence, ' ');
        int n = words.size();
        vi dp(n+1,INF);
        // w[i-0], w[i]+w[i-1]+1, w[i]+w[i-1]+w[i-2]+2..., w[i]+...w[i-k]+k
        // dp[i] = min(dp[i-x-1]+f([i-x:i])), x in [0,p)  
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int s = words[i-1];
            dp[i] = dp[i-1] + (k-s)*(k-s);
            for (int j = i-1; j >= 1; --j) {
                s += 1+words[j-1];
                if (s > k) break;
                dp[i] = min(dp[i], dp[j-1]+(k-s)*(k-s));
            }
        }
        int ans = dp[n-1], s = words[n-1];
        for (int i = n-1; i >= 1; --i) {
            s += 1+words[i-1];
            if (s > k) break;
            ans = min(ans, dp[i-1]);
        }
        return ans;
    }
};