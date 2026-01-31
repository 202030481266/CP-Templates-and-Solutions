#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int mask[8][130];
bool flag = false;

void init() {
    if (flag) return;
    flag = true;
    int x = 0;
    for (int i = 1; i < 8; ++i) { // 1 ~ 7
        for (int j = 1; j < (1<<i); ++j) {
            x = __builtin_popcount(j);
            if (x == 2 || x == 3 || x == 4) {
                mask[i][j] = 1;
            }
        }
    }
}

class Solution {
public:
    int countPairs(vector<int>& nums) {
        // 组合数计算 : C(7,2) * 1 + C(7,3) * 2 + C(7,4) * 6 = 301
        init();
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        unordered_map<int, int> cnt;
        for (int &v : nums) cnt[v]++;
        int ans = 0;
        // construct the valid numbers
        for (int i = 0; i < n-1; ++i) {
            cnt[nums[i]]--;
            // 0
            ans += cnt[nums[i]];
            string s = to_string(nums[i]);
            int N = s.size();
            vector<int> tmp;
            for (int j = 1; j < (1<<N); ++j) {
                if (mask[N][j]) {
                    vector<int> pos;
                    for (int k = 0; k < 7; ++k) {
                        if ((j >> k) & 1) pos.push_back(k);
                    }
                    int m = pos.size();
                    if (m == 2 && s[pos[0]] != s[pos[1]]) {
                        // 2
                        swap(s[pos[0]], s[pos[1]]);
                        tmp.push_back(stoi(s));
                        // back
                        swap(s[pos[0]], s[pos[1]]);
                    }
                    if (m == 3 && s[pos[0]] != s[pos[1]] && s[pos[0]] != s[pos[2]] && s[pos[1]] != s[pos[2]]) {
                        // 1 2 3
                        swap(s[pos[0]], s[pos[1]]); // 2 1 3
                        swap(s[pos[0]], s[pos[2]]); // 3 1 2
                        tmp.push_back(stoi(s));
                        // back
                        swap(s[pos[0]], s[pos[2]]); // 2 1 3
                        swap(s[pos[1]], s[pos[2]]); // 2 3 1
                        tmp.push_back(stoi(s));
                        swap(s[pos[1]], s[pos[2]]); // 2 1 3
                        swap(s[pos[0]], s[pos[1]]); // 1 2 3
                    }
                    if (m == 4) {
                        // 1 + 2, 3 + 4
                        if (s[pos[0]] != s[pos[1]] & s[pos[2]] != s[pos[3]]) {
                            swap(s[pos[0]], s[pos[1]]);
                            swap(s[pos[2]], s[pos[3]]);
                            tmp.push_back(stoi(s));
                            // back
                            swap(s[pos[2]], s[pos[3]]);
                            swap(s[pos[0]], s[pos[1]]);
                        }
                        // 1 + 3, 2 + 4
                        if (s[pos[0]] != s[pos[2]] && s[pos[1]] != s[pos[3]]) {
                            swap(s[pos[0]], s[pos[2]]);
                            swap(s[pos[1]], s[pos[3]]);
                            tmp.push_back(stoi(s));
                            // back
                            swap(s[pos[1]], s[pos[3]]);
                            swap(s[pos[0]], s[pos[2]]);
                        }
                        // 1 + 4, 2 + 3
                        if (s[pos[0]] != s[pos[3]] && s[pos[1]] != s[pos[2]]) {
                            swap(s[pos[0]], s[pos[3]]);
                            swap(s[pos[1]], s[pos[2]]);
                            tmp.push_back(stoi(s));
                            // back
                            swap(s[pos[1]], s[pos[2]]);
                            swap(s[pos[0]], s[pos[3]]);
                        }
                    }
                }
            }
            sort(tmp.begin(), tmp.end());
            int pre = -1;
            for (int i = 0; i < tmp.size(); ++i) {
                if (tmp[i] != pre) {
                    ans += cnt[tmp[i]];
                    pre = tmp[i];
                }
            }
        }
        return ans;
    }
};