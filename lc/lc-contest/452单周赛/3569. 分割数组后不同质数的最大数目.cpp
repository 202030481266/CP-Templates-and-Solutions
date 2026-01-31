// https://leetcode.cn/problems/maximize-count-of-distinct-primes-after-split/description/

static constexpr int maxn = 100001;
int mp[maxn], n, m;
int isprime[maxn];
set<int> pos[10001];

vector<int> generate_primes_linear_time(int n) {
    vector<int> lp(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            isprime[i] = 1;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    return primes;
}
bool flag = false;

void init() {
    flag = true;
    auto primes = generate_primes_linear_time(maxn-1);
    for (int i = 0; i < primes.size(); i++) {
        mp[primes[i]] = i;
    }
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid+1, r

int mx[maxn<<2];
int lazy[maxn<<2];

void pushup(int rt) {
    mx[rt] = max(mx[ls], mx[rs]);
}

void pushdown(int rt) {
    if (lazy[rt]) {
        mx[ls] += lazy[rt];
        mx[rs] += lazy[rt];
        lazy[ls] += lazy[rt];
        lazy[rs] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    mx[rt] = 0;
    lazy[rt] = 0;
    if (l == r) {
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        mx[rt] += val;
        lazy[rt] += val;
        return;
    }
    pushdown(rt);
    if (R <= mid) update(lson, L, R, val);
    else if (L > mid) update(rson, L, R, val);
    else {
        update(lson, L, mid, val);
        update(rson, mid+1, R, val);
    }
    pushup(rt);
}

void update(int primeIdx, int val) {
    if (pos[primeIdx].empty()) return;
    int l = *pos[primeIdx].begin(), r = *pos[primeIdx].rbegin();
    if (r > l) {
        update(1, 0, n-1, l, r-1, val); 
    }
}

class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        if (!flag) init();
        n = nums.size(); 
        m = queries.size();
        for (int i = 0; i < n; ++i) {
            if (isprime[nums[i]]) {
                pos[mp[nums[i]]].clear();
            }
        }
        for (int i = 0; i < m; ++i) {
            if (isprime[queries[i][1]]) {
                pos[mp[queries[i][1]]].clear();
            }
        }
        set<int> have;
        for (int i = 0; i < n; ++i) {
            if (isprime[nums[i]]) {
                pos[mp[nums[i]]].insert(i);
                have.insert(mp[nums[i]]);
            }
        }
        build(1, 0, n-1);
        int tot = have.size(); 
        for (int k : have) {
            update(k, 1);
        }
        vector<int> ans;
        for (int i = 0; i < m; ++i) {
            int idx = queries[i][0], val = queries[i][1], k;
            if (isprime[nums[idx]]) {
                k = mp[nums[idx]];
                update(k, -1);
                pos[k].erase(idx);
                if (pos[k].empty()) tot--;
                else update(k, 1);
            }
            if (isprime[val]) {
                k = mp[val];
                update(k, -1);
                pos[k].insert(idx);
                if (pos[k].size() == 1) tot++;
                else update(k, 1);
            }
            nums[idx] = val;
            ans.push_back(tot + mx[1]);
        }
        return ans;
    }
};