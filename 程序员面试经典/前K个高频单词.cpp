using pis = pair<int, string>;
class Solution {
public:
    int comp(const pis& x, const pis& y) { // x < y
        if (x == y) return 2;
        else if (x.first < y.first || (x.first == y.first && x.second > y.second)) return 0;
        return 1;
    }
    void qsort(vector<pis>& a, int l, int r, int k) {
        if (l == r) return;
        pis c = a[(l + r) >> 1];
        int i = l - 1, j = r + 1;
        while (i < j) {
            while (comp(a[++i], c) == 0); //  < 
            while (comp(a[--j], c) == 1); //  > 
            if (i < j) swap(a[i], a[j]);
        }
        int cnt = j - l + 1;
        if (k <= cnt) qsort(a, l, j, k);
        else qsort(a, j + 1, r, k - cnt);
    }
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnt;
        for (string& v : words)
            cnt[v] += 1;
        vector<pis> arr;
        for (auto& kv : cnt)
            arr.emplace_back(kv.second, kv.first);
        int m = arr.size();
        qsort(arr, 0, m - 1, m + 1 - k);
        // 因为答案需要排序，所以无论如何都是需要排序最后的结果
        sort(arr.begin() + m - k, arr.end(),[](const pis&x, const pis& y){
            return x.first == y.first ? x.second < y.second : x.first > y.first;
        });
        vector<string> ans;
        for (int i = m - k; i < m; ++i)
            ans.push_back(arr[i].second);
        return ans;
    }
};