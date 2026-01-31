#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    int distinctPoints(string s, int k) {
        int n = s.size();
        vector<int> offsetX(n + 1), offsetY(n + 1);
        vector<pii> arr;
        for (int i = 1; i <= n; ++i) {
            offsetX[i] = offsetX[i - 1] + (s[i - 1] == 'L' ? -1 : s[i - 1] == 'R' ? 1 : 0);
            offsetY[i] = offsetY[i - 1] + (s[i - 1] == 'D' ? -1 : s[i - 1] == 'U' ? 1 : 0);
            if (i >= k) {
                arr.emplace_back(offsetX[i] - offsetX[i - k], offsetY[i] - offsetY[i - k]);
            }
        }
        ranges::sort(arr);
        int i = 0, ans = 0;
        while (i < arr.size()) {
            int j = i + 1;
            ++ans;
            while (j < arr.size() && arr[j] == arr[i]) ++j;
            i = j;
        }
        return ans;
    }
};