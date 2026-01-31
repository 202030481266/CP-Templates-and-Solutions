// 二分查找绝世好题
class Solution {
public:
    long long sums[200005] = {0};
    long long floorDiv(long long x, long long y) {
        if(y < 0) x = -x, y = -y;
        if(x < 0) return (x - (y - 1)) / y;
        return x / y;
    }
    long long ceilDiv(long long x, long long y) {
        if(y < 0) x = -x, y = -y;
        if(x < 0) return x / y;
        return (x + (y - 1)) / y;
    }
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        for(int v : nums2) sums[v + 100000]++;
        for(int i = 1; i <= 200000; ++i) sums[i] += sums[i-1];

        auto sum = [&](long long x) -> long long {
            if(x < -100000) return 0;
            if(x > 100000) return sums[200000];
            return sums[x + 100000];
        };

        long long l = -1e10, r = 1e10;
        while(l < r) {
            long long m = (l + r) >> 1;
            
            long long cnt = 0;
            for(int v : nums1) {
                if(v < 0) cnt += sum(100000) - sum(ceilDiv(m, v) - 1);
                if(v == 0 && m >= 0) cnt += nums2.size();
                if(v > 0) cnt += sum(floorDiv(m, v));
            }

            if(cnt < k) l = m + 1;
            else r = m;
        }

        return l;
    }
};