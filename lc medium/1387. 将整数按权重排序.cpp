#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// colatz 猜想不存在已经知道的上界
// 但是可以对于每一个计算的数字都是步骤数都不会很大
int dp[1001];
bool flag = 0;

void init() {
    for (int i = 1; i <= 1000; ++i) {
        ll x = i;
        int steps = 0;
        while (x != 1) {
            steps++;
            if (x % 2 == 0) {
                x /= 2;
            } else {
                x = 3 * x + 1;
            }
        }
        dp[i] = steps;
    }
}

class Solution {
public:
    int getKth(int lo, int hi, int k) {
        if (!flag) {
            init();
            flag = 1;
        }
        vector<int> arr;
        for (int i = lo; i <= hi; ++i) {
            arr.push_back(i);
        }
        nth_element(arr.begin(), arr.begin() + k - 1, arr.end(), [&](int a, int b) {
            return dp[a] == dp[b] ? a < b : dp[a] < dp[b];
        });
        return arr[k-1];
    }
};