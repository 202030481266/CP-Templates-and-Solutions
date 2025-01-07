class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
    int a[100001];
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size(), mx = 0;  
        UnionFind un(n + 1);
        for (int i = 0; i < n; ++i) {
            if (a[nums[i]]) 
                un.unite(a[nums[i]], i + 1);
            a[nums[i]] = i + 1;
            if (nums[i] > mx) mx = nums[i];
        }
        for (int i = 2; i <= mx; ++i) {
            int f = -1;
            for (int j = i; j <= mx; j += i) {
                if (a[j]) {
                    if (f == -1) f = a[j];
                    else un.unite(f, a[j]);
                }
            }
        }
        // 分为了几个可排序的集合
        vector<int> arr[n + 1];
        for (int i = 1; i <= n; ++i)
            arr[un.find(i)].push_back(i - 1);
        for (int i = 1; i <= n; ++i) {
            if (!arr[i].empty()) {
                vector<int> tmp;
                sort(arr[i].begin(), arr[i].end());
                for (int j = 0; j < arr[i].size(); ++j) tmp.push_back(nums[arr[i][j]]);
                sort(tmp.begin(), tmp.end());
                for (int j = 0; j < arr[i].size(); ++j)
                    nums[arr[i][j]] = tmp[j];
            }
        }
        return is_sorted(nums.begin(), nums.end());
    }
};