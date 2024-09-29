#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

// 简单的递归

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int n = operations.size(), m = 0;
        vector<ll> p{1};
        while (p.back() < k) {
            p.push_back(p.back() * 2);
        }
        m = p.size();
        function<int(ll)> dfs = [&](ll i) -> int {
            if (i == 1) return 0;
            int j = 0;
            while (p[j] < i) ++j;
            ll tmp = i - p[j-1];
            if (operations[j-1] == 0) {
                return dfs(tmp);
            }
            else {
                return (dfs(tmp)+1)%26;
            }
        };
        return (char)(dfs(k)+'a');
    }
};