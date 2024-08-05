#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


// 这道题比第三道题思维难度小很多，但是实现上非常麻烦
// 本质上还是set<int>维护一个区间有序列表，然后用哈希表维护其中的大小
// 难点在于环区间维护，实际上分块做也挺好的

// 1*a1 + 2*a2 + 3*a3 + 4*a4 + ... + n*an
// a3, a4, a5, a6
// 1*a3 + 2*a4 + 3*a5 + 4*a6
// 3*a3 + 4*a4 + 5*a5 + 6*a6
// 2*(a3+a4+a6)

// [0,i]
template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] += value;
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    // returns min(p | sum[0..p] >= sum)
    // requires non-negative tree values
    int lower_bound(T sum) {
        int highest_one_bit = 1;
        while (highest_one_bit << 1 <= t.size())
            highest_one_bit <<= 1;
        int pos = 0;
        // 使用倍增的方法来进行查找
        for (size_t blockSize = highest_one_bit; blockSize != 0; blockSize >>= 1) {
            int p = pos + blockSize - 1;
            if (p < t.size() && t[p] < sum) {
                sum -= t[p];
                pos += blockSize;
            }
        }
        return pos;
    }
};

class Solution {
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        vector<int> arr(colors.begin(),colors.end());
        for (int i = 0; i < n-1; ++i) arr.push_back(colors[i]);
        set<pii> s;//里面所有的区间都是连续的，并且不重不漏
        fenwick<ll> t1(n+1), t2(n+1);
        int left = 0, pre = colors[0], N = 2*n-1;
        auto update = [&](int l, int r, int val) {
            if (r >= n) return;
            int ind = r-l+1;
            t1.add(ind,ind*val);
            t2.add(ind,val);
        };
        auto debug = [&]() {
            cerr<< "-----------------" << endl;
            for (auto p : s) {
                cerr <<p.first << ' ' << p.second << endl;
            }
            cerr << "----------------" << endl;
        };
        for (int i = 1; i < N; ++i) {
            if (arr[i] == pre) {
                s.insert({left, i-1});
                update(left, i-1, 1);
                left = i;
                pre = arr[i];
            }
            else pre ^= 1;
        }
        s.insert({left, N-1});
        update(left, N-1, 1);
        auto f = [&](int i, int val) {
            if (arr[i]==val) return;
            // 找到包含的区间
            auto it = s.upper_bound({i, inf});
            assert(it != s.begin()); // 肯定不是一开始的位置
            it = prev(it); // [l,r] that must l <= i
            // 在区间中，又有两种情况： 边界或者内部
            arr[i] = val;
            if (it->first < i && it->second > i) {
                // [it->first, i-1],[i,i], [i+1, it->second]
                int left = it->first, right = it->second;
                update(it->first, it->second, -1);
                update(it->first, i-1, 1);
                update(i+1, it->second, 1);
                update(i,i,1);
                s.insert({i+1, it->second});
                s.insert({it->first, i-1});
                s.insert({i,i});
                s.erase({it->first, it->second});
            }
            else {
                // 在边界上
                assert(it->first == i || it->second == i);
                if (it->first == i && it->second == i) {
                    // 单个元素区间
                    // 可能发生双合并
                    if (it != s.begin() && next(it) != s.end()) {
                        assert(prev(it)->second == i-1 && next(it)->first == i+1);
                        update(prev(it)->first, prev(it)->second, -1);
                        update(next(it)->first, next(it)->second, -1);
                        update(i,i,-1);
                        update(prev(it)->first, next(it)->second, 1);
                        int l = prev(it)->first, r = next(it)->second;
                        // 这里的删除要十分小心
                        s.erase(prev(it));
                        s.erase(next(it));
                        s.erase(it);
                        s.insert({l,r});
                    }
                    // 剩下的肯定是只能左合并或者右合并
                    else if (it != s.begin()) {
                        assert(prev(it)->second == i-1);
                        update(prev(it)->first, prev(it)->second, -1);
                        update(i,i,-1);
                        update(prev(it)->first,i,1);
                        int l = prev(it)->first;
                        s.erase(prev(it));
                        s.erase(it);
                        s.insert({l,i});
                    }
                    else if (it != s.end()) {
                        assert(next(it)->first == i+1);
                        update(next(it)->first, next(it)->second, -1);
                        update(i,i,-1);
                        update(i,next(it)->second,1);
                        int r = next(it)->second;
                        s.erase(next(it));
                        s.erase(it);
                        s.insert({i,r});
                    }
                    return;
                }
                if (it->first == i){ // 左合并代码
                    if (it != s.begin()) { // 这个区间可以增加
                        int l = prev(it)->first, r = prev(it)->second;
                        assert(r==i-1);
                        update(l,r,-1);
                        update(l,i,1);
                        s.insert({l,i});
                        s.erase({l,r});
                    }
                    update(i, it->second, -1);
                    update(i+1, it->second, 1);
                    s.insert({i+1,it->second});
                    s.erase({i,it->second});
                }
                else { // 右边合并代码
                    if (next(it) != s.end()) { // 这个区间可以加1
                        int l = next(it)->first, r = next(it)->second;
                        assert(l==i+1);
                        update(l, r, -1);
                        update(i, r,1); 
                        s.insert({i,r});
                        s.erase({l,r});
                    }
                    update(it->first,i, -1);
                    update(it->first,i-1, 1);
                    s.insert({it->first,i-1});
                    s.erase({it->first,i});
                }
            }
            return;
        };
        vector<int> ans;
        for (auto& q : queries) {
            if (q[0]==1) {
                // query
                int sz = q[1]; 
                ll x = t1.sum(n)-t1.sum(sz-1);// sz*a[sz]+(sz+1)*a[sz+1]...n*a[n]
                ll y = t2.sum(n)-t2.sum(sz-1);// a[sz]+a[sz+1]...a[n]
                ll res = x-(sz-1)*y; // 1*a[sz]+2*a[sz+1]+3*a[sz+2]...(n-sz+1)*a[n]
                // 找到最后一个区间，就是 l <= n-1 and r >= n
                auto it = s.lower_bound({n, -1});
                assert(it != s.begin());
                it = prev(it);
                int l = it->first, r=it->second;
                //[l,n-1], (r-l+1)-sz+1=r-l-sz+2
                ans.push_back(res+max(0,min(n-l,r-l-sz+2)));
            }
            else {
                // 更新两个地方
                f(q[1],q[2]);
                if (q[1]+n < N)
                    f(q[1]+n,q[2]);
            }
        }
        return ans;
    }
};