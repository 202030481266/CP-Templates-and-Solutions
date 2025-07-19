#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int isprime[100005];

void init() {
    for (int i = 2; i <= 100000; ++i) isprime[i] = 1;
    for (int i = 2; i * i <= 100000; ++i) {
        if (isprime[i]) {
            for (int j = i * i; j <= 100000; j += i) {
                isprime[j] = 0;
            }
        }
    }
}

int flag;

class Solution {
public:
    long long splitArray(vector<int>& nums) {
        if (!flag) {
            init();
            flag = 1;
        }
        int n = nums.size();
        ll sa = 0, sb = 0;
        for (int i = 0; i < n; ++i) {
            if (isprime[i]) sa += nums[i];
            else sb += nums[i];
        }
        return abs(sa - sb);
    }
};