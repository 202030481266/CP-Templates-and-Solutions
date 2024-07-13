// https://www.luogu.com.cn/problem/P3763
// string hash can caculate two string is equal or not in O(1)
// binary search + string hash is typical solution
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

const int MAXN = 100001;
const int base = 499;

vector<long long> p(MAXN);
vector<long long> hashs(MAXN);
vector<long long> hashp(MAXN);

void build(const string& s, int n, const string& ss, int m) {
    p[0] = 1;
    for (int j = 1; j < MAXN; j++) {
        p[j] = p[j - 1] * base;
    }
    hashs[0] = s[0] - 'a' + 1;
    for (int j = 1; j < n; j++) {
        hashs[j] = hashs[j - 1] * base + s[j] - 'a' + 1;
    }
    hashp[0] = ss[0] - 'a' + 1;
    for (int j = 1; j < m; j++) {
        hashp[j] = hashp[j - 1] * base + ss[j] - 'a' + 1;
    }
}

long long hash_value(const vector<long long>& hash, int l, int r) {
    long long ans = hash[r];
    if (l != 0) {
        ans -= hash[l - 1] * p[r - l + 1];
    }
    return ans;
}

bool same(int l1, int l2, int len) {
    return hash_value(hashs, l1, l1 + len - 1) == hash_value(hashp, l2, l2 + len - 1);
}

bool check(int l1, int r1, int k) { // close interval writing style
    int diff = 0;
    int l2 = 0;
    while (l1 <= r1 && diff <= k) {
        int l = 1;
        int r = r1 - l1 + 1;
        int len = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (same(l1, l2, m)) {
                len = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (l1 + len <= r1) {
            diff++;
        }
        l1 += len + 1;
        l2 += len + 1;
    }
    return diff <= k;
}

int compute(const string& s, const string& p, int k) {
    int n = s.size();
    int m = p.size();
    if (n < m) {
        return 0;
    }
    build(s, n, p, m);
    int ans = 0;
    for (int i = 0; i <= n - m; i++) {
        if (check(i, i + m - 1, k)) {
            ans++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore(); // To ignore the newline character after the integer input

    for (int i = 0; i < n; i++) {
        string s, p;
        getline(cin, s);
        getline(cin, p);
        cout << compute(s, p, 3) << "\n";
    }

    return 0;
}
