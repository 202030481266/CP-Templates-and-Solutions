// 模板题目 https://www.luogu.com.cn/problem/P3370
// video url https://www.bilibili.com/video/BV1hu4m1A7AF
// The String hash used to solve the problem of string comparison

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int N = 1510;
const int p = 499;

char s[N];

int solve() {
    unordered_set<ull> cnt;
    int n;
    cin >> n;
    while (n--) {
        cin >> s;
        int len = strlen(s);
        ull h = 0;
        for (int i = 0; i < len; ++i) {
            h = h*p + s[i];
        }
        cnt.insert(h);
    }
    return cnt.size();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve() << endl;
}