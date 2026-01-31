// https://leetcode.cn/problems/random-point-in-non-overlapping-rectangles/

// 随机数生成器类
class RandomGenerator {
private:
    std::mt19937_64 gen;  // 使用64位梅森旋转算法
    std::uniform_int_distribution<long long> dist;
    
public:
    // 构造函数，初始化随机数生成器和分布范围
    RandomGenerator() {}
    RandomGenerator(long long min_val, long long max_val) : 
        gen(std::random_device()()), // 使用随机设备初始化生成器
        dist(min_val, max_val) {
    }
    
    // 使用种子初始化的构造函数
    RandomGenerator(long long min_val, long long max_val, unsigned seed) : 
        gen(seed), // 使用指定种子初始化
        dist(min_val, max_val) {
    }
    
    // 获取一个随机数
    long long getRandomNumber() {
        return dist(gen);
    }
    
    // 设置新的范围
    void setRange(long long min_val, long long max_val) {
        dist = std::uniform_int_distribution<long long>(min_val, max_val);
    }
    
    // 重置随机数生成器的种子
    void reseed(unsigned seed) {
        gen.seed(seed);
    }
};

class Solution {
public:
    vector<vector<int>> rects;
    vector<int> sum;
    vector<vector<RandomGenerator>> rectG;
    RandomGenerator rg;
    int n;
    int area(const vector<int>& rect) {
        return (rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
    }
    Solution(vector<vector<int>>& R) {
        n = R.size();
        this->rects = R;
        sum.reserve(n);
        sum[0] = area(rects[0]);
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i-1] + area(rects[i]);
        }
        rectG.resize(n);
        for (int i = 0; i < n; ++i) {
            auto& r = rects[i];
            rectG[i].emplace_back(0, r[2] - r[0]);
            rectG[i].emplace_back(0, r[3] - r[1]);
        }
        rg = RandomGenerator(1, sum[n-1]);
    }
    
    vector<int> pick() {
        // pick the rectangle
        int pos = (int)rg.getRandomNumber();
        int l = -1, r = n;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (sum[mid] >= pos) r = mid;
            else l = mid;
        }
        int rx = (int)rectG[r][0].getRandomNumber();
        int ry = (int)rectG[r][1].getRandomNumber();
        return {rects[r][0] + rx, rects[r][1] + ry};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */