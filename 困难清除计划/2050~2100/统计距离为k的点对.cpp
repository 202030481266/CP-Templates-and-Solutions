class Solution {
    typedef unsigned long long ull;
    unordered_map<ull, int> pos;
    int cnt[50001];
public:
    int countPairs(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        int ans = 0; 
        ull offset = 1e6 + 1;
        vector<ull> arr;
        for (auto& c : coordinates)
            arr.push_back(c[0] * offset + c[1]);
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        int m = arr.size();
        for (int i = 0; i < m; ++i) pos[arr[i]] = i;
        for (int a = 0; a <= k; ++a) {
            int b = k - a;
            memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i < n; ++i) {
                ull x = coordinates[i][0] ^ a, y = coordinates[i][1] ^ b;
                if (pos.count(x * offset + y))
                    ans += cnt[pos[x * offset + y]];
                ++cnt[pos[coordinates[i][0] * offset + coordinates[i][1]]];
            }
        }
        return ans;
    }
};