#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;



class Solution {
public:
    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {
        // 算法复杂度 (N-n)*(M-m)*n*m，最坏情况就是O(25^4),390625=400000
        unordered_map<char, vector<pii>> mp;
        unordered_map<int, vector<pii>> mp2;
        unordered_map<int, bool> use;
        int n = pattern.size(), m = pattern[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (isalpha(pattern[i][j])) {
                    mp[pattern[i][j]].emplace_back(i, j);
                }
                else {
                    mp2[pattern[i][j] - '0'].emplace_back(i, j);
                }
            }
        }
        int N = board.size(), M = board[0].size();
        for (int i = 0; i + n - 1 < N; ++i) {
            for (int j = 0; j + m - 1 < M; ++j) {
                bool flag = true;
                use.clear();
                for (auto [k,v] : mp) {
                    int tmp = board[v[0].first+i][v[0].second+j];
                    if (use.count(tmp)) {
                        flag = false;
                        break;
                    }
                    use[tmp] = true;
                    for (auto [x, y] : v) {
                        if (board[i+x][j+y] != tmp) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) continue;
                for (auto [k,v] : mp2) {
                    for (auto [x, y] : v) {
                        if (board[i+x][j+y] != k) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) break;
                }
                if (flag) return {i,j};
            }
        }
        return {-1,-1};
    }
};