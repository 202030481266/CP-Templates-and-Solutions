using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int cnt[100000];
int c[100000];

class Solution {
public:
    int minCost(vector<int>& nums1, vector<int>& nums2) {
        vi arr;
        for (int v : nums1) arr.push_back(v);
        for (int v : nums2) arr.push_back(v);
        for (int v : arr) cnt[v] = c[v] = 0;
        for (int v : arr) ++cnt[v];
        for (int v : arr) {
            if (cnt[v] & 1) return -1;
        }
        for (int v : nums1) ++c[v];
        int ans = 0;
        for (int v : arr) {
            ans += abs(cnt[v] / 2 - c[v]);
            cnt[v] = c[v] = 0;
        }
        return ans / 2;
    }
};