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
    int minimumKeypresses(string s) {
        vector<int> cnt(26);
        for (char& c : s) cnt[c-'a']++;
        sort(all(cnt));
        int ans = 0, one = 9, two = 9;
        for (int i = 25; i >= 0; --i) {
            if (!cnt[i]) break;
            if (one) {
                --one;
                ans += cnt[i];
            }
            else if (two) {
                --two;
                ans += 2 * cnt[i];
            }
            else {
                ans += 3 * cnt[i];
            }
        }
        return ans;
    }
};