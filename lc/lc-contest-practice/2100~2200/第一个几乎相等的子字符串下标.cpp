#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

// 字符串哈希 + 二分
const int p = 499;

class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        // 二分的思想
        int n = s.size(), m = pattern.size();
        vector<ull> h(n+1), hp(m+1), pp(n+1);
        pp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pp[i] = pp[i-1] * p;
        }
        for (int i = 1; i <= n; ++i) {
            h[i] = h[i-1]*p + (s[i]-'a'+1);
        }
        for (int i = 1; i <= m; ++i)  {
            hp[i] = hp[i-1]*p + (pattern[i]-'a'+1);
        }
        auto get_hash_s = [&](int l, int r) -> ull {
            return h[r] - h[l-1] * pp[r - l +1];
        };
        auto get_hash_p = [&](int l, int r) -> ull {
            return hp[r] - hp[l-1] * pp[r - l +1];
        };
        int ans = -1;
        for(int i = 1; i <= n - m + 1; ++i){
            int left = 1, right = m, pos = m + 1;
            // 二分查找第一个不匹配的位置
            while (left <= right) {
                int mid = left + (right - left) /2;
                ull hash_s = get_hash_s(i, i + mid -1);
                ull hash_p = get_hash_p(1, mid);
                if(hash_s == hash_p){
                    left = mid + 1;  
                }
                else{
                    pos = mid;
                    right = mid - 1;
                }
            }
            if (pos == m + 1 || pos == m) {
                return i-1;
            }
            ull hash_s_suffix = get_hash_s(i + pos, i + m -1);
            ull hash_p_suffix = get_hash_p(pos +1, m);
            if (hash_s_suffix == hash_p_suffix) {
                return i-1;
            }
        }
        return -1; 
    }
};

