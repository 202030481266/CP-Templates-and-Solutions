class Solution {
public:
    int maxSubstringLength(string s) {
        int n = s.size();
        vector<int> left(26, -1);
        vector<int> right(26, -1);
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (left[c] == -1) left[c] = right[c] = i;
            else right[c] = i;
        }
        int ans = -1;
        vector<pair<int, int>> arr;
        for (int i = 0; i < 26; ++i) {
            if (left[i] != -1) {
                // 自扩展，这里每一次扩展最多都是线性的
                int l = left[i], r = l, nl = l, nr = right[i];
                while (l > nl || r < nr) {
                    while (l > nl) {
                        nl = min(left[s[--l] - 'a'], nl);
                        nr = max(right[s[l] - 'a'], nr);
                    }
                    while (r < nr) {
                        nl = min(left[s[++r] - 'a'], nl);
                        nr = max(right[s[r] - 'a'], nr);
                    } 
                }
                if (l > 0 || r < n - 1) {
                    arr.emplace_back(l, r);
                }
            }
        }
        sort(arr.begin(), arr.end());
        // 下面不相容的区间拼接最大值
        for (int i = 0; i < arr.size(); ++i) {
            int l = arr[i].first, r = arr[i].second;
            for (int j = i + 1; j < arr.size(); ++j) {
                if (arr[j].first > r) {
                    if (arr[j].first == r + 1 && (l > 0 || arr[j].second < n - 1))
                        r = arr[j].second;
                    else break;
                } 
            }
            // [i, j)
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};