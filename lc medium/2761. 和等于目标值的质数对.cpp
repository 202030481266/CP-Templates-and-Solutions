#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

vector<int> generate_primes_linear_time(int n) {
    vector<int> lp(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    return primes;
}

class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        vector<int> primes = generate_primes_linear_time(n);
        int m = primes.size(), i = 0, j = m - 1;
        vector<vector<int>> ans;
        while (i <= j) {
            int sum = primes[i] + primes[j];
            if (sum == n) {
                ans.push_back({primes[i], primes[j]});
                ++i, --j;
            }
            else if (sum > n) {
                --j;
            }
            else {
                ++i;
            }
        }
        return ans;
    }
};