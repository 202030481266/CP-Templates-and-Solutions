#include <bits/stdc++.h>
using namespace std;

struct ST {

    long long N;
    vector<vector<long long>> vec;

    ST() {}
    ST(int n) {
        N = n;
        vec.resize(N);
        for (auto &v : vec) v = vector<long long>(30, 0);
        for (int i = 0; i < N; i++) {
            cin >> vec[i][0]; 
        }
    }
    ST(const vector<long long>&a) {
        vec.resize(a.size());
        N = a.size();
        for (auto &v : vec) v = vector<long long>(30, 0);
        for (int i = 0; i < N; i++) vec[i][0] = a[i];
    }
    void ST_work() {
        int t = log(N) / log(2) + 1;
        for (int i = 1; i < t; i++) {
            for (int j = 0; j + (1 << i) - 1 < N; j++) {
                vec[j][i] = max(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    long long query(int l, int r) {
        int k = log(r - l + 1) / log(2);
        return max(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};