#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        if (m == 1) return {0};

        vector<int> mx(n+1, 0);
        int p = m-1;
        for (int i = n-1; i >= 0; --i) {
            mx[i] = mx[i+1];
            if (p >= 0 && word1[i] == word2[p]) {
                mx[i]++;
                p--;
            }
        }

        vector<int> first_p(m, -1);
        for (int i = 0, j = 0; i < n && j < m; ++i) {
            if (word1[i] == word2[j]) {
                first_p[j] = i;
                j++;
            }
        }

        int j = 0;
        vector<int> ans;
        for (int i = 0; i < m && j < n; ++i) {
            // not equal , (i, m)
            if (j+1 < n && mx[j+1] >= m-i-1) {
                int x = j, y = i;
                // greedy match
                while (x < n && y < m && word1[x] == word2[y]) {
                    ans.push_back(x);
                    ++x;
                    ++y;
                }
                if (x < n && y < m) {
                    ans.push_back(x);
                    ++x;
                    ++y;
                }
                for (; x < n && y < m; ++x) {
                    if (word1[x] == word2[y]) {
                        ans.push_back(x);
                        ++y;
                    }
                }
                break;
            }
            // must equal
            if (first_p[i] == -1) {
                return {};
            }
            ans.push_back(first_p[i]);
            j = first_p[i] + 1;
        }
        return (ans.size() == m ? ans : vector<int>{});
    }
};