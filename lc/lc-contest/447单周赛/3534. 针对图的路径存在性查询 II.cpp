#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int jump[100005][20];

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            vector<int>& q = queries[i];
            if (nums[q[0]] == nums[q[1]]) {
                if (q[0] != q[1]) ans[i] = 1;
            }
            q[0] = nums[q[0]];
            q[1] = nums[q[1]];
            q.push_back(i);
            if (q[0] < q[1]) swap(q[0], q[1]);
        }
        sort(queries.begin(), queries.end());
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        n = nums.size();
        int l = 0, p = 0;
        for (int i = 0; i < n && p < queries.size(); ++i) {
            for (int j = 0; j < 20; ++j) jump[i][j] = -1;
            while (nums[i] - nums[l] > maxDiff) ++l;
            if (l < i) {
                jump[i][0] = l;
                for (int j = 1; j < 20; ++j) {
                    if (jump[i][j - 1] != -1)
                        jump[i][j] = jump[jump[i][j - 1]][j - 1];
                }
            }
            while (p < queries.size() && queries[p][0] == nums[i]) {
                int x = queries[p][1], id = queries[p][2], k = i;
                if (x < nums[i]) {
                    for (int j = 19; j >= 0; --j) {
                        if (jump[k][j] != -1 && nums[jump[k][j]] >= x) {
                            ans[id] += (1 << j);
                            k = jump[k][j];
                        }
                    }
                    int sub = abs(nums[k] - x);
                    if (sub > maxDiff) ans[id] = -1;
                    else if (sub != 0) ans[id]++;
                }
                ++p;
            }
        }
        return ans;
    }
}; 