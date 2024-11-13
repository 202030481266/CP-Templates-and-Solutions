#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        ll ans = 0;
        int n = word.size();
        vector<int> cnt1(5), cnt2(5);

        auto f = [&](vector<int> c) -> bool {
            for (int v : c) 
                if (!v) return false;
            return true;
        };

        unordered_map<char, int> pos = {{'a',0}, {'e',1}, {'i',2}, {'o', 3}, {'u', 4}};
        int l1 = 0, l2 = 0, c1 = 0, c2 = 0;
        for (int i = 0; i < n; ++i) {
            char ch = word[i];
            if (pos.count(ch)) ++cnt1[pos[ch]], ++cnt2[pos[ch]];
            else ++c1, ++c2;
            while (c1 >= k && f(cnt1)) {
                if (pos.count(word[l1])) --cnt1[pos[word[l1]]];
                else --c1;
                l1++;
            }
            while (c2 > k && f(cnt2)) {
                if (pos.count(word[l2])) --cnt2[pos[word[l2]]];
                else --c2;
                l2++;
            }
            // [l2, l1)
            if (l1 > l2 && f(cnt2) && c2 == k) {
                ans += l1 - l2;
            }
        }
        return ans;
    }
};