class FrequencyTracker {
    unordered_map<int, int> cnt;
    unordered_map<int, int> fre;
public:
    FrequencyTracker() { cnt.clear(); }
    
    void add(int number) {
        int tmp = cnt[number];
        ++cnt[number];
        --fre[tmp];
        ++fre[tmp + 1];
    }
    
    void deleteOne(int number) {
        if (cnt[number]) {
            int tmp = cnt[number];
            --cnt[number];
            --fre[tmp];
            ++fre[tmp - 1];
        }
    }
    
    bool hasFrequency(int frequency) {
        return fre[frequency] > 0;
    }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */