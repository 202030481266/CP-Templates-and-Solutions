#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    int score(vector<string>& cards, char x) {
        int n = cards.size(), m = 0;
        vector<int> cnt1(26), cnt2(26);
        for (int i = 0; i < n; ++i) {
            if (cards[i][0] == x && cards[i][1] == x) ++m;
            else if (cards[i][0] == x) {
                ++cnt1[cards[i][1] - 'a'];
            }
            else if (cards[i][1] == x) {
                ++cnt2[cards[i][0] - 'a'];
            }
        }
        int ans = 0;
        int mx1 = *max_element(cnt1.begin(), cnt1.end()), mx2 = *max_element(cnt2.begin(), cnt2.end());
        int sum1 = accumulate(cnt1.begin(), cnt1.end(), 0), sum2 = accumulate(cnt2.begin(), cnt2.end(), 0);
        for (int i = 0; i <= m; ++i) {
            int n1 = max(mx1, i), n2 = max(mx2, m - i);
            int s1 = (sum1 + i - n1) >= n1 ? (sum1 + i) / 2 : sum1 + i - n1;
            int s2 = (sum2 + m - i - n2) >= n2 ? (sum2 + m - i) / 2 : sum2 + m - i - n2;
            ans = max(ans, s1 + s2);
        }
        return ans;
    }
};