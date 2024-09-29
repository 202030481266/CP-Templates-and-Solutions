// https://loj.ac/p/114

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n , m;

int clz(long long x) {
    if (x == 0) return 64; // 如果 x 为 0，返回 64（所有位都是零）

    int count = 0;
    while ((x & (1LL << 63)) == 0) { // 检查最高位
        count++;
        x <<= 1; // 左移 x
    }
    return count;
}

void solve() {
    cin >> n;
    vector<ll> basis;
    ll tmp;
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        for (ll b : basis) {
            tmp = min(tmp, tmp ^ b);
        }
        if (tmp) basis.push_back(tmp);
        else flag = 1;
    }
    // 标准化
    sort(basis.begin(), basis.end(), greater<ll>());
    for (int i = 0; i < basis.size(); ++i) {
        for (int j = i + 1; j < basis.size(); ++j) {
            int hb = 63 - clz(basis[j]); // __builtin_clz() 函数会出错
            if (basis[i] & (1ll << hb)) {
                basis[i] ^= basis[j];
            }
        }
    }
    cin >> m;
    int N = basis.size();
    ll cnt = (1ll<<N)-1, k;
    while (m--) {
        cin >> k;
        k -= flag;
        if (!k) {
            cout << 0 << '\n';
            continue;
        }
        if (k > cnt) {
            cout << -1 << '\n';
            continue;
        }
        ll ans = 0;
        for (int i = N-1; i >= 0; --i) {
            if (k & (1ll<<i)) {
                ans ^= basis[N-i-1];
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}

/*

对拍函数

#pragma once
#include "dbg.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>        
#include <iostream>       
#include <iomanip>
#include <sstream>         
#include <stdexcept>
#include <algorithm>       
#include <cmath>           
#include <numeric>
#include <functional>
#include <complex>
#include <list>
#include <vector>         
#include <stack>
#include <queue>
#include <deque>          
#include <bitset>        
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <ctime>
#include <optional>
#include <cstdint>

using namespace std;


// 构造整数随机数据
// 梅森素数旋转算法
vector<int> get_random_data(size_t times, int lower, int upper) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> u(lower, upper);
    vector<int> res;
    for (int i = 0; i < times; i++)
        res.emplace_back(u(gen));
    return res;
}
string get_random_alpha_string(size_t length) {
    auto index = get_random_data(length, 0, 25);
    string res;
    for (int i = 0; i < length; i++) res += char(index[i] + 'a');
    return res;
}
string get_random_digit_string(size_t length) {
    auto index = get_random_data(length, 0, 9);
    string res;
    for (int i = 0; i < length; i++) res += char(index[i] + '0');
    return res;
}

// get leetcode vector
string integerVectorToString(vector<int> list, int length = -1) {
    if (length == -1) {
        length = list.size();
    }
    if (length == 0) {
        return "[]";
    }
    string result;
    for (int index = 0; index < length; index++) {
        int number = list[index];
        result += to_string(number) + ", ";
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}



typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;

int clz(long long x) {
    if (x == 0) return 64; // 如果 x 为 0，返回 64（所有位都是零）

    int count = 0;
    while ((x & (1LL << 63)) == 0) { // 检查最高位
        count++;
        x <<= 1; // 左移 x
    }
    return count;
}

void solve(vector<int>& arr) {
    vector<ll> basis;
    int flag = 0, n = arr.size();
    for (int i = 0; i < n; ++i) {
        ll tmp = arr[i];
        for (ll b : basis) {
            tmp = min(tmp, tmp ^ b);
        }
        if (tmp) basis.push_back(tmp);
        else flag = 1;
    }
    // 标准化
    sort(basis.begin(), basis.end(), greater<ll>());
    int N = basis.size();
    vector<ll> ys;
    vector<ll> xs;
    vector<ll> zs;
    if (flag) zs.push_back(0), ys.push_back(0);
    for (int i = 1; i < (1 << N); ++i) {
        ll res = 0;
        for (int j = 0; j < N; ++j) {
            if (i & (1 << j)) res ^= basis[j];
        }
        zs.push_back(res);
    }
    for (int i = 0; i < basis.size(); ++i) {
        for (int j = i + 1; j < basis.size(); ++j) {
            int hb = 63 - clz(basis[j]);
            if (basis[i] & (1ll << hb)) {
                basis[i] ^= basis[j];
            }
        }
    }
    // test the linear basis
    for (int i = 0; i < basis.size(); ++i) {
        int x = 63 - clz(basis[i]);
        for (int j = 0; j < basis.size(); ++j) {
            if (j != i) {
                assert((basis[j] & (1ll<<x))==0);
            }
        }
    }
    // construct the result
    for (int i = 1; i < (1 << n); ++i) {
        ll res = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) res ^= arr[j];
        }
        xs.push_back(res);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    vector<ll> ans;
    if (flag) ans.push_back(0);
    for (int i = 1; i < (1 << N); ++i) {
        ll res = 0, t = 0;
        for (int j = 0; j < N; ++j) {
            if (i & (1 << j)) {
                res ^= basis[j];
                t ^= basis[N - 1 - j];
            }
        }
        ys.push_back(res);
        ans.push_back(t);
    }
    sort(zs.begin(), zs.end());
    sort(ys.begin(), ys.end());
    assert(xs.size() == zs.size() && xs.size() == ys.size() && xs.size() == ans.size());
    int m = xs.size();
    for (int i = 0; i < m; ++i) {
        assert(xs[i] == zs[i] && xs[i] == ys[i] && xs[i] == ans[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for (int i = 1; i <= 20; ++i) {
        vector<int> test_case = get_random_data(i, 1, INT_MAX - 1);
        solve(test_case);
        cout << "test case " << i << " pass!" << '\n';
    }
    return 0;
}
*/