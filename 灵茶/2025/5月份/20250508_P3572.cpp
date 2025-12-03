// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_3572.cpp
# Author: xiaoshulin
# Created Time: 2021/10/13 11:27:21
#########################################################################*/
 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int inf = 0x3f3f3f3f;

int a[maxn], dp[maxn];
int n, m, k, q[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> m;
    int head, tail;
    while (m--) {
        cin >> k;
        head = tail = 1; 
        q[tail] = 1;
        for(int i = 2; i <= n; i++) {
            while(head <= tail && i - q[head] > k) head++;
            if(a[q[head]] > a[i]) dp[i] = dp[q[head]];
            else dp[i] = dp[q[head]] + 1;
            while(head <= tail && (dp[q[tail]] > dp[i]) || (dp[q[tail]] == dp[i] && a[q[tail]] <= a[i])) tail--;
            q[++tail] = i;
        }
        cout << dp[n] << "\n";
    }
    return 0;
}