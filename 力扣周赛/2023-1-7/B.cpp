class DataStream {
public:
    int value, k;
    vector<int> sum{0};
    DataStream(int value, int k) {
        this->value = value;
        this->k = k;
    }
    
    bool consec(int num) {
        sum.emplace_back(sum.back() + (num == value));
        int n = sum.size();
        if (n < k + 1) return false;
        else return sum[n - 1] - sum[n - k - 1] == k;
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */