#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// f1 = A1 + |x - B1| , f2 = A2 + |x - B2|
// |A1 - A2| >= |B1 - B2|, max(f1, f2) = f2 (A2 > A1)
// |A1 - A2| < |B1 - B2|, max(f1, f2) = (A2+A1+B2-B1)/2 + |x - (A2-A1+B2+B1)/2| (B1 <= B2)

// 恶心的题目，不想做第二次
// O(nlogn)做法，就是左边划分的最大值，然后找到最优解
// 最优解一定是一个划分，不然可以反证（证明方法是贪心）
// 因此可以使用排序快速逐步往前枚举就可以了

int floor_div(int a, int b) {
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) < 0)) {
        q -= 1;
    }
    return q;
}

int ceil_div(int a, int b) {
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}

class Solution {
public:
    int minDifference(vector<int>& nums) {
        vector<pii> a, b;
        int l = -1, n = nums.size(), ans = 0, flag = 0;
        for (int i = 0; i < n; ++i) {
            if (i+1 < n && nums[i] != -1 && nums[i+1] != -1)
                ans = max(ans, abs(nums[i]-nums[i+1]));
            if (nums[i] == -1) {
                if (l == -1) l = i;
            }
            else {
                // [l, i)
                if (l != -1) {
                    if (i-l == 1) {
                        if (l == 0) {
                            a.push_back({nums[i],nums[i]});
                            b.push_back({nums[i],nums[i]});
                        }
                        else {
                            int pre = nums[l-1], suf = nums[i];
                            a.push_back({min(pre,suf), max(pre,suf)});
                            b.push_back({min(pre,suf), max(pre,suf)});
                        }
                    }
                    else {
                        if (l == 0) {
                            a.push_back({nums[i], nums[i]});
                            b.push_back({nums[i], nums[i]});
                        }
                        else {
                            int pre = nums[l-1], suf = nums[i];
                            flag = 1;
                            a.push_back({min(pre,suf), max(pre,suf)});
                            b.push_back({pre,pre});
                            b.push_back({suf,suf});
                        }
                    }
                    l = -1;
                }
            }
        }
        if (l != -1 && l != 0) {
            a.push_back({nums[l-1], nums[l-1]});
            b.push_back({nums[l-1], nums[l-1]});
        }

        if (a.size() == 0) return ans;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        auto f = [&](vector<pii>& arr) -> int {
            int res = INT_MAX;
            int n = arr.size(), i = 0;
            vector<int> mx(n);
            mx[n-1] = arr[n-1].second;
            for (int i = n-2; i >= 0; --i) mx[i]=max(mx[i+1],arr[i].second);
            while (i < n) {
                int p = i;
                while (p < n && arr[p].second <= arr[i].second) ++p;
                // [i,p)
                int t = (arr[i].second-arr[0].first+1)/2;
                int tmp = (p < n ? max(t,(mx[p]-arr[p].first+1)/2) : t);
                res = min(res, tmp);
                i = p;
            }
            return res;
        };
        auto g = [&](vector<pii>& arr) -> int {
            int res = INT_MAX;
            int n = arr.size(), i = 0;
            vector<int> mx(n);
            mx[n-1] = arr[n-1].second;
            for (int i = n-2; i >= 0; --i) mx[i]=max(mx[i+1],arr[i].second);
            while (i < n) {
                int p = i;
                while (p < n && arr[p].second <= arr[i].second) ++p;
                int t = (arr[i].second-arr[0].first+1)/2;
                double x = 1.0*(arr[i].second+arr[0].first)/2;
                if (p < n) {
                    int s = (mx[p]-arr[p].first+1)/2;
                    double y = 1.0*(mx[p]+arr[p].first)/2;
                    int dis=floor(fabs(x-y));
                    if (dis <= max(s,t)) {
                        res = min(res, max(s,t));
                    }
                    else {
                        int ms = max(s,t), ns = min(s,t), sub = ms-ns, rem = dis-sub;
                        if (rem <= ms) res = min(res, ms);
                        else res = min(res, ms + ((rem-ms) % 3 == 0 ? (rem-ms) / 3 : (rem-ms) / 3 + 1));
                    }
                }
                else res = min(res, t);
                i = p;
            }
            return res;
        };

        int ans1 = f(a), ans2 = flag ? g(b) : INT_MAX;
        return max(ans, min(ans1, ans2));
    }
};


// O(n) 做法
// 相当有思维量，依然贪心，但是不用排序
// 因为我们只在于最大值和最小值，所以根本上我们对于每一个区间都可以单独做决定
// 每个区间对于最后的贡献其实是独立的，这样就可以使用贪心！这是本题最为关键的一个观察

class Solution {
public:
    int minDifference(vector<int>& nums) {
        vector<pair<int,int>> a, b;
        int l = -1, n = nums.size(), ans = 0, flag = 0;
        int mn = INT_MAX/2, mx = 0;
        for (int i = 0; i < n; ++i) {
            if (i+1 < n && nums[i] != -1 && nums[i+1] != -1)
                ans = max(ans, abs(nums[i]-nums[i+1]));
            if (nums[i] == -1) {
                if (l == -1) l = i;
            }
            else {
                // [l, i)
                if (l != -1) {
                    if (i-l == 1) {
                        if (l == 0) {
                            a.push_back({nums[i],nums[i]});
                            b.push_back({nums[i],nums[i]});
                        }
                        else {
                            int pre = nums[l-1], suf = nums[i];
                            a.push_back({min(pre,suf), max(pre,suf)});
                            b.push_back({min(pre,suf), max(pre,suf)});
                        }
                    }
                    else {
                        if (l == 0) {
                            a.push_back({nums[i], nums[i]});
                            b.push_back({nums[i], nums[i]});
                        }
                        else {
                            int pre = nums[l-1], suf = nums[i];
                            flag = 1;
                            a.push_back({min(pre,suf), max(pre,suf)});
                            b.push_back({pre,pre});
                            b.push_back({suf,suf});
                        }
                    }
                    l = -1;
                }
            }
        }
        if (l != -1 && l != 0) {
            a.push_back({nums[l-1], nums[l-1]});
            b.push_back({nums[l-1], nums[l-1]});
        }

        for (auto& e : a) {
            mn = min(mn, min(e.first, e.second));
            mx = max(mx, max(e.first, e.second));
        }

        int left = mn, right = mx;
        for (auto& x : a) {
            int l = x.first, r = x.second;
            if (r-mn < mx-l) left = max(left, r);
            else right = min(right, l);
            if (right == mn || left == mx) break;
        }
        int ans1 = (left-mn+1)/2, ans2 = (mx-right+1)/2;
        int res = max(ans1, ans2);

        if (flag) {
            left = mn, right = mx;
            for (auto& x : b) {
                int l = x.first, r = x.second;
                if (r-mn < mx-l) left = max(left, r);
                else right = min(right, l);
                if (right == mn || left == mx) break;
            }
            ans1 = (left-mn+1)/2;
            ans2 = (mx-right+1)/2;
            if (ans1 < ans2) swap(ans1, ans2);
            double pre = 1.0*(left+mn)/2, suf = 1.0*(right+mx)/2;
            int dis = floor(fabs(suf-pre)), sub = ans1 - ans2;
            if (dis-sub > ans1) {
                int rm = dis-sub-ans1; 
                int k = rm/3, t = rm%3;
                return max(ans, min(res, t ? ans1 + k + 1 : ans1 + k));
            }
            return max(ans, min(ans1, res));
        }
        return max(ans, res);
    }
};