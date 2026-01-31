#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        vector<int> a;
        for (auto& s : sentence) {
            a.push_back(s.size());
        }
        int n = sentence.size(), sum = accumulate(a.begin(), a.end(), 0);
        int cycle = sum+n-1, p = 0;
        vector b(n, vector<int>(n+1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                b[i][j+1] = b[i][j] + a[(i+j)%n];
            }
            for (int j = 1; j <= n; ++j) {
                b[i][j] += j;
            }
        }
        int ans = 0;
        for (int i = 0; i < rows; ++i) {
            int x = (cols+1) / (cycle+1), rem = cols - x*(cycle+1) + 1;
            int mx = upper_bound(b[p].begin(), b[p].end(), rem) - b[p].begin();
            // [0,mx)
            ans += x;
            p += (mx-1);
            if (p >= n) {
                ans++;
                p %= n;
            }
        }
        return ans;
    }
};