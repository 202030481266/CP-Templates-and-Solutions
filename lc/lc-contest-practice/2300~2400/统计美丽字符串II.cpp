// 前缀和 + 哈希表套路经典题目
// 关键在于分解质因数分析
class Solution {
    int p_sqrt(int n) {
        int res = 1;
        for (int i = 2; i * i <= n; i++) {
            int i2 = i * i;
            // 尝试分离两倍
            while (n % i2 == 0) {
                res *= i;
                n /= i2;
            }
            if (n % i == 0) {
                res *= i;
                n /= i;
            }
        }
        if (n > 1) {
            res *= n;
        }
        return res;
    }

    const int AEIOU_MASK = 1065233;

public:
    long long beautifulSubstrings(string s, int k) {
        k = p_sqrt(k * 4);
        // 把 pair 压缩成 long long（或者 int）就可以用 umap 了
        map<pair<int, int>, int> cnt;
        cnt[{k - 1, 0}]++; // 添加 (k-1, sum)
        long long ans = 0;
        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            int bit = (AEIOU_MASK >> (s[i] - 'a')) & 1;
            sum += bit * 2 - 1; // 1 -> 1    0 -> -1
            ans += cnt[{i % k, sum}]++;
        }
        return ans;
    }
};

