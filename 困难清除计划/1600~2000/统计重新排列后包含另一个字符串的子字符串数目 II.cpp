#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

// 就是一个简单的滑动窗口

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        // 维护一个最短的可行指针
        vector<int> cnt(26), cur(26);
        for (char c : word2) cnt[c-'a']++;
        int l = 0, k = 0, tot = 0;
        ll ans = 0;
        for (int i = 0; i < 26; ++i) tot += (cnt[i] > 0 ? 1 : 0);
        for (int i = 0; i < n; ++i) {
            int c = word1[i] - 'a';
            ++cur[c];
            if (cnt[c] && cur[c] == cnt[c]) ++k; // valid
            while (k == tot) {
                int t = word1[l++]-'a';
                --cur[t];
                if (cur[t] == cnt[t]-1) --k;
            }
            //[0,l)
            ans += l;
        }
        return ans;
    }
};