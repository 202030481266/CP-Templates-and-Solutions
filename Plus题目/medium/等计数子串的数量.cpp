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
    int equalCountSubstrings(string s, int count) {
        int res = 0;
        for (int n = 1; n <= 26; n++) {
            unordered_map<char, int> hash;
            for (int i = 0, j = 0, cnt = 0; i < s.size(); i++) {
                if (hash[s[i]] == count) cnt--;
                hash[s[i]]++;
                if (hash[s[i]] == count) cnt++;
                while (i - j + 1 > n * count) {
                    if (hash.count(s[j]) && hash[s[j]] == count) cnt--;
                    if (--hash[s[j]] == 0) hash.erase(s[j]);
                    if (hash.count(s[j]) && hash[s[j]] == count) cnt++; 
                    j++;
                }
                if (hash.size() == n && n == cnt) res++;
            }
        }
        return res;
    }
};