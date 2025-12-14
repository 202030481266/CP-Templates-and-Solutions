#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid 
#define rson rs,mid+1,r

int sum[MAXN << 2], cnt[MAXN << 2], arr[MAXN]; 

void pushup(int rt, int l, int r) {
    sum[rt] = sum[ls] + sum[rs];
    cnt[rt] = cnt[ls] + cnt[rs];
    if (arr[mid] && arr[mid + 1]) --cnt[rt];
}

void build(int rt, int l, int r) {
    if (l == r) {
        sum[rt] = cnt[rt] = arr[l];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt, l, r);
}

void update(int rt, int l, int r, int pos) {
    if (l == r) {
        arr[l] ^= 1;
        sum[rt] = cnt[rt] = arr[l];
        return;
    }
    if (pos <= mid) update(lson, pos);
    else update(rson, pos);
    pushup(rt, l, r);
}

pii query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return {sum[rt], cnt[rt]};
    if (R <= mid) return query(lson, L, R);
    if (L > mid) return query(rson, L, R);
    auto [lsum, lcnt] = query(lson, L, mid);
    auto [rsum, rcnt] = query(rson, mid + 1, R);
    if (arr[mid + 1] && arr[mid]) return {lsum + rsum, lcnt + rcnt - 1};
    return {lsum + rsum, lcnt + rcnt};
}

class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();       
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'A') arr[i + 1] = 1;
            else arr[i + 1] = 0;
        }
        build(1, 1, n);
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                update(1, 1, n, q[1] + 1);
            }
            else {
                int l = q[1] + 1, r = q[2] + 1, len = r - l + 1;
                auto [s, c] = query(1, 1, n, l, r);
                // cout << l << ' ' << r << ' ' << s << ' ' << c << endl;
                if (arr[l]) {
                    if (arr[r]) {
                        // AAAABBBBAAAABBB...A
                        ans.push_back((s - c) + (len - s - c + 1));
                    }
                    else {
                        // AAAABBBBAAAABBB...B
                        ans.push_back((s - c) + (len - s - c));
                    }
                }
                else {
                    if (arr[r]) {
                        // BBBBAAAABBB...A
                        ans.push_back((s - c) + (len - s - c));
                    }
                    else {
                        // BBBBAAAABBB...AAAABBB
                        ans.push_back((s - c) + (len - s - c - 1));
                    }
                }
            }
        }
        return ans;
    }
};©leetcode