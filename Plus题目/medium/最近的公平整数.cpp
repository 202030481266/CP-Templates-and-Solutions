#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


// 一道模拟题目，但是非常考验编程水平
// 大多数题解都是直接枚举的，但是模拟分类讨论更加有思维含量，并且难度一定是 hard

class Solution {
public:
    int closestFair(int N) {
        // 如果n是奇数，那么答案很简单， 1 0 0 0 ... 1 1 1
        // 偶数的话，9的处理相对麻烦
        string num = to_string(N);
        vector<int> digits;
        for (char ch : num) {
            digits.push_back(ch - '0');
        }
        int n = num.size();
        if (n & 1) {
            ++n;
            string ans(n, '0');
            ans[0] = '1';
            // [n-n/2+1, n-1]
            for (int i = n / 2 + 1; i < n; ++i) {
                ans[i] = '1';
            }
            return stoi(ans);
        }
        int odd = 0, even = 0;
        for (int v : digits) {
            if (v & 1) ++odd;
            else ++even;
        }
        int change = abs(odd-even);
        assert(change % 2 == 0);
        if (change == 0) return N;
        change /= 2;
        if (even > odd) {
            int p = -1;
            for (int i = n-1; i >= 0; --i) {
                if (digits[i] % 2 == 0) {
                    if (change) --change;
                }
                if (change == 0) {
                    p = i;
                    break;
                }
            }
            assert(p != -1 && digits[p] % 2 == 0);
            // [p,n-1] should be change
            digits[p] += 1;  // 变成第一个大于digits[p]的奇数
            // 后面全部变成1
            for (int i = p + 1; i < n; ++i) {
                digits[i] = 1;
            }
        }
        else {
            // 不像把偶数变成了奇数，永远是可以找到一个合适的值
            // 把奇数变成偶数会困难的多
            // a little bit trick
            int p = -1; 
            for (int i = n-1; i >= 0; --i) {
                if (digits[i] & 1) {
                    if (change) --change;
                }
                if (change == 0 && digits[i] < 8) {
                    p = i;
                    break;
                }
            }
            if (p == -1) {
                // 意味着前缀是一个 9999 类型的数字
                // 我们需要做的只能是扩充一个位置
                n += 2;
                string ans = "1";
                // [1,n/2]
                for (int i = 1; i <= n/2; ++i) ans += "0";
                for (int i = n/2+1; i < n; ++i) ans += "1";
                return stoi(ans);
            }
            else {
                // [p,n-1] 修正
                // 这里很有难度
                change = abs(odd-even)/2;
                for (int i = p; i < n; ++i) {
                    if (digits[i] % 2== 0) ++even;
                }
                even += change;
                if (digits[p] % 2 == 0) {
                    // 表明是偶数，那么就需要加 2，不然只会有一个后果，那就是增加了奇数，后面无论如何修改都无效
                    digits[p] += 2;
                }
                else {
                    // 这个就可以使得这个数字为偶数
                    digits[p] += 1;
                }
                --even;
                // [p,n-1], n-p
                // odd -> odd-change, even -> even + change
                for (int i = p+1; i < n; ++i){
                    if (even) digits[i]=0, --even;
                    else digits[i]=1;
                }
            }
        }
        string ans;
        for (int digit : digits) {
            ans += to_string(digit);
        }
        return stoi(ans);
    }
};