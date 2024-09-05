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

/*
给定一个二进制字符串 s 和一个正整数 k。

你可以对字符串应用以下操作任意次数:
从 s 中选择任何大小为 k 的子字符串，将其所有字符翻转，即将所有 1 都变成 0，所有 0 都变成 1。

返回您可以获得的不同字符串的数量。因为答案可能太大，所以对 10^9 + 7 取模后返回。

注意:
- 二进制字符串是仅由字符 0 和 1 组成的字符串。
- 子字符串是字符串的连续部分。
*/
ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

class Solution {
public:
    int countDistinctStrings(string s, int k) {
        int n = s.size(); 
        return quick_pow(2, n-k+1);
    }
};




