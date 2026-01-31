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
    bool isPreorder(vector<vector<int>>& nodes) {
        int n = nodes.size();
        vector<int> stk;
        vector<bool> instack(n);
        if (nodes[0][1] != -1) return false;
        stk.push_back(nodes[0][0]);
        instack[nodes[0][0]] = true;
        for (int i = 1; i < n; ++i) {
            if (instack[nodes[i][0]] || !instack[nodes[i][1]]) return false;
            while (!stk.empty() && stk.back() != nodes[i][1]) {
                instack[stk.back()] = false;
                stk.pop_back();
            }
            if (stk.empty()) return false;
            else { 
                stk.push_back(nodes[i][0]);
                instack[nodes[i][0]] = true;
            }
        }
        return true;
    }
};