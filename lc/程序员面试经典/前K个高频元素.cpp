class Solution {
public:
    using pii = pair<int, int>;
    void quick_select(vector<pii>& a, int l, int r, int k) {
        if (l == r) return;
        int mid = a[(l + r) >> 1].second, i = l - 1, j = r + 1;
        while (i < j) {
            while (a[++i].second < mid);
            while (a[--j].second > mid);
            if (i < j) swap(a[i], a[j]);
        }
        int cnt = j - l + 1;
        if (k <= cnt) quick_select(a, l, j, k);
        else quick_select(a, j + 1, r, k - cnt);
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 要么是哈希表统计然后变成前K大的问题，要么使用堆来实现算法，总之不难
        unordered_map<int, int> cnt;
        for (int& v : nums) cnt[v] += 1;

        vector<pii> arr;
        for (auto& kv : cnt)
            arr.push_back(kv);
        quick_select(arr, 0, arr.size() - 1, arr.size() + 1 - k);
        vector<int> ans;
        for (int i = arr.size() - 1; i >= (int)arr.size() - k; --i) {
            ans.push_back(arr[i].first);
        }
        return ans;
    }
};
