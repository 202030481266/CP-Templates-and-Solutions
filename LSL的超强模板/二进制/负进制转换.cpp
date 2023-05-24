// 无论K是正数还是负数都支持（只支持-10～10进制，因为更高进制需要引入字母）
vector<int> baseK(int N, int K) {
    if (N == 0) return {0};
    vector<int> res;
    while (N != 0) {
        int r = ((N % K) + abs(K)) % abs(K); // 此处为关键
        res.push_back(r);
        N -= r;
        N /= K;
    }
    reverse(res.begin(), res.end());
    return res;
}