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

class Solution {
public:
    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& buildings) {
        vi arr;
        for (auto& b : buildings) {
            arr.push_back(b[0]);
            arr.push_back(b[1]);
        }
        sort(all(arr));
        arr.erase(unique(all(arr)), arr.end());
        int n = arr.size();
        vector<int> cnt(n+1);
        vector<int> sum(n+1);
        for (auto& b : buildings) {
            b[0] = lower_bound(all(arr), b[0]) - arr.begin();
            b[1] = lower_bound(all(arr), b[1]) - arr.begin();
            ++cnt[b[0]];
            --cnt[b[1]];
            sum[b[0]] += b[2];
            sum[b[1]] -= b[2];
        }
        int cur = 0, num = 0, l = -1, avg = -1;
        vector<vector<int>> ans;
        for (int i = 0; i < n; ++i) {
            num += cnt[i];
            cur += sum[i];
            if (num == 0) {
                if (avg != -1) {
                    ans.push_back({l, i, avg});
                }
                avg = -1;
                l = -1;
            }
            else if (avg == -1) {
                avg = cur / num;
                l = i;
            }
            else {
                if (cur / num != avg) {
                    ans.push_back({l, i, avg}); // [l,i)
                    avg = cur / num;
                    l = i;
                }
            }
        }
        for (auto& r : ans) {
            r[0] = arr[r[0]];
            r[1] = arr[r[1]];
        }
        return ans;
    }
};
