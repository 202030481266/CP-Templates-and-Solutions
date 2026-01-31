#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return position[a] < position[b];
        });
        int ans = 0, i = n-1;
        while (i >= 0) {
            double time = (double)(target - position[ids[i]]) / speed[ids[i]];
            int j = i-1;
            while (j >= 0 && position[ids[j]] + speed[ids[j]] * time >= target) j--;
            ++ans;
            i = j;
        }
        return ans;
    }
};