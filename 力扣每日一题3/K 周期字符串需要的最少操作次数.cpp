#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int base = 233;

class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        int n = word.size(); 
        unordered_map<ull, int> mp;
        for (int i = 0; i < n; i += k) {
            ull hash = 0;
            for (int j = i; j < i+k; ++j) {
                hash = hash * base + word[j];
            }
            mp[hash]++;
        }
        int res = 0;
        for (auto [u, v] : mp) {
            res = max(res, v);
        }
        return n/k - res;
    }
};
