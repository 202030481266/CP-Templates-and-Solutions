#include <bits/stdc++.h>
using namespace std;

// 枚举做运算的两个字符，然后贪心算就可以了。
// 较大的数看做1，较小的数看做-1。
// 把这当成求最大子数组和的问题

int largestVariance(string &s) {
        int ans = 0;
        for (char a = 'a'; a <= 'z'; ++a)
            for (char b = 'a'; b <= 'z'; ++b) {
                if (a == b) continue;
                int diff = 0, diff_with_b = -s.length();
                for (char ch : s) {
                    if (ch == a) {
                        ++diff;
                        ++diff_with_b;
                    } else if (ch == b) {
                        diff_with_b = --diff;
                        diff = max(diff, 0);
                    }
                    ans = max(ans, diff_with_b);
                }
            }
        return ans;
}
