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
    int brightestPosition(vector<vector<int>>& lights) {
        vpii arr;
        for (auto& light : lights) {
            arr.emplace_back(light[0]-light[1], 1);
            arr.emplace_back(light[0]+light[1]+1, -1);
        }
        sort(all(arr));
        int ans = -1, mx = -1, cur = 0;
        for (auto [p, w] : arr) {
            cur += w;
            if (cur > mx) {
                ans = p;
                mx = cur;
            }
        }
        return ans;
    }
};