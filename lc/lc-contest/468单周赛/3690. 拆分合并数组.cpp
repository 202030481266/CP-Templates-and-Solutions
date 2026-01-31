#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 康托展开 + bfs最短路
//
static constexpr int pw[] = {1, 1, 2, 6, 24, 120, 720}; 

class Solution {
public:
    int getRankFromPermutation(const std::vector<int>& perm) {
        int n = perm.size();
        int rank = 0;
        for (int i = 0; i < n; ++i) {
            int smaller_count = 0;
            for (int j = i + 1; j < n; ++j) {
                if (perm[j] < perm[i]) {
                    smaller_count++;
                }
            }
            rank += smaller_count * pw[n - 1 - i];
        }
        return rank;
    }

    std::vector<int> getPermutationFromRank(int rank, const std::vector<int>& original_elements) {
        int n = original_elements.size();
        std::vector<int> perm; 
        std::vector<int> available_nums = original_elements;
        std::sort(available_nums.begin(), available_nums.end());

        for (int i = n - 1; i >= 0; --i) {
            int factorial = pw[i];
            if (factorial == 0 && rank > 0) {
                return {};
            }
            int index = rank / factorial;
            if (index >= available_nums.size()) {
                return {}; 
            }
            perm.push_back(available_nums[index]);
            available_nums.erase(available_nums.begin() + index);
            rank %= factorial;
        }
        
        return perm;
    }

    int minSplitMerge(vector<int>& a, vector<int>& b) {
        int n = a.size();
        vector<int> dis(pw[n] + 1, inf);
        int start = getRankFromPermutation(a);
        dis[start] = 0;
        queue<vector<int>> q;
        q.emplace(a);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            int rk = getRankFromPermutation(u);
            for (int i = 0; i < n; ++i) {
                for (int j = i; j < n; ++j) {
                    vector<int> nxt;
                    vector<int> seg(u.begin() + i, u.begin() + j + 1); // [i, j + 1)
                    for (int k = 0; k < i; ++k) nxt.push_back(u[k]);
                    for (int k = j + 1; k < n; ++k) nxt.push_back(u[k]);
                    for (int k = 0; k <= nxt.size(); ++k) {
                        vector<int> tmp = nxt;
                        tmp.insert(tmp.begin() + k, seg.begin(), seg.end());
                        int rank = getRankFromPermutation(tmp);
                        if (dis[rank] > dis[rk] + 1) {
                            dis[rank] = dis[rk] + 1;
                            q.emplace(tmp);
                        }
                    }
                }
            }
        }
        int target = getRankFromPermutation(b);
        return dis[target];
    }
};