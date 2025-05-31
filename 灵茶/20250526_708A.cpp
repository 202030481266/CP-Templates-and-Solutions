// https://codeforces.com/problemset/problem/708/A
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    string ans;
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a', pre = (c + 25) % 26;
        if (pre < c) {
        	int j = i;
            for (; j < n; ++j) {
                pre = (s[j] - 'a' + 25) % 26;
                if (pre < s[j] - 'a')
                	ans.push_back(pre + 'a');
                else break;
            }
            for (; j < n; ++j) {
            	ans.push_back(s[j]);
            }
            break;
        }
        ans.push_back(s[i]);
    }
    cout << ans << endl;
}