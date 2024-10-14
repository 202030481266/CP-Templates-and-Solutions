#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 细节处理：
// k-x的维护的集合 a 有可能为空
// 乘法结果可能超过INT_MAX

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        vector<ll> ans;
        int n = nums.size();
        
        if (k == x) { // accelerate
            ll s = 0;
            int l = 0;
            for (int i = 0; i < n; ++i) {
                s += nums[i];
                if (i - l >= k) s -= nums[l++];
                if (i - l == k-1) ans.push_back(s);
            }
            return ans;
        }


        set<pair<int,int>> a,b;
        unordered_map<int, int> cnt;
        ll sum = 0;

        int l = 0;
        for (int i = 0; i < n; ++i) {
            // add
            if (b.size() < x) {
                // means we can add it directly
                if (!cnt.count(nums[i])) {
                    b.insert({1, nums[i]});
                    cnt[nums[i]] = 1;
                    sum += nums[i];
                }
                else {
                    b.erase({cnt[nums[i]], nums[i]});
                    ++cnt[nums[i]];
                    b.insert({cnt[nums[i]], nums[i]});
                    sum += nums[i];
                }
            }
            else {
                auto bf = make_pair(b.begin()->first, b.begin()->second);
                if (!cnt.count(nums[i])) {
                    // maybe bigger than the smallest one in b
                    auto mx = make_pair(1, nums[i]);
                    if (mx > bf) {
                        b.erase(b.begin());
                        b.insert(mx);
                        sum += nums[i] - 1ll * bf.first * bf.second;
                        a.insert(bf);
                    }
                    else {
                        a.insert({1, nums[i]});
                    }
                    cnt[nums[i]] = 1;
                }
                else {
                    auto ib = b.lower_bound({cnt[nums[i]], nums[i]});
                    if (ib != b.end() && ib->second == nums[i]) {
                        // in b
                        b.erase({cnt[nums[i]], nums[i]});
                        ++cnt[nums[i]];
                        b.insert({cnt[nums[i]], nums[i]});
                        sum += nums[i];
                    }
                    else {
                        // in a
                        a.erase({cnt[nums[i]], nums[i]});
                        ++cnt[nums[i]];
                        auto pi = make_pair(cnt[nums[i]], nums[i]);
                        if (pi > bf) {
                            a.insert(bf);
                            b.erase(b.begin());
                            b.insert(pi);
                            sum += 1ll * pi.first * pi.second - 1ll * bf.first * bf.second;
                        }
                        else {
                            a.insert(pi);
                        }
                    }
                }
            }
            // del
            if (i - l >= k) {
                int v = nums[l++];
                auto ib = b.lower_bound({cnt[v], v});
                pii mx; // should prevent a is empty
                if (a.empty()) mx = make_pair(0,0);
                else mx = make_pair(prev(a.end())->first, prev(a.end())->second);
                if (cnt[v] == 1) {
                    if (ib != b.end() && ib->second == v) {
                        // in b
                        b.erase(ib);
                        sum -= cnt[v] * v;
                        if (mx.first > 0) {
                            b.insert(mx);
                            sum += 1ll * mx.first * mx.second;
                            a.erase(prev(a.end()));
                        }
                    }
                    else {
                        // in a
                        a.erase({1, v});
                    }
                    cnt.erase(v);//cnt[v] = 0
                }
                else {
                    auto pv = make_pair(cnt[v]-1, v);
                    if (ib != b.end() && ib->second == v) {
                        // in b
                        b.erase(ib);
                        sum -= 1ll * cnt[v] * v;
                        // comparison
                        if (pv > mx) {
                            b.insert(pv);
                            sum += 1ll * pv.first * pv.second;
                        }
                        else {
                            b.insert(mx);
                            sum += 1ll * mx.first * mx.second;
                            a.erase(prev(a.end()));
                            a.insert(pv);
                        }
                    }
                    else {
                        // in a
                        a.erase({cnt[v], v});
                        a.insert(pv);
                    }
                    cnt[v]--;
                }
            }
            if (i - l == k-1) {
                ans.push_back(sum);
            }
        }
        return ans;
    }
};