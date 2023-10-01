// 格雷编码问题
// 可以通过镜像构造和归纳推导，最简单的方法是使用公式
vector<int> Gray_Create(int n) {
    vector<int> res;
    for (int i = 0; i < (1 << n); ++i)
        res.emplace_back(i ^ (i >> 1));
    return res;
}