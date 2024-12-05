#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e6 + 7;
int lp[maxn]; 
vector<int> primes;
void generate_min_divisors(int n) {
    lp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
}
int init = 0;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        if (!init) {
            init = 1;
            generate_min_divisors(1000000);
        }
        int ans = 0, n = nums.size();
        for (int i = n-2; i >= 0; --i) {
            while (nums[i] > nums[i+1]) {
                if (lp[nums[i]] == nums[i]) return -1;
                nums[i] = lp[nums[i]];
                ans++;
            }
        }
        return ans;
    }
};