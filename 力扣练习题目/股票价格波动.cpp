class StockPrice {
private:
    set<pair<int,int>> s;
    unordered_map<int, int> hs;
    int maxx = 0;
public:
    StockPrice() {}
    
    void update(int timestamp, int price) {
        if (hs.count(timestamp) == 0) {
            maxx = max(maxx, timestamp);
        }
        else {
            auto it = s.find(make_pair(hs[timestamp], timestamp));
            s.erase(it);
        }
        s.emplace(price, timestamp);
        hs[timestamp] = price;
    }
    
    int current() {
        return hs[maxx];
    }
    
    int maximum() {
        return s.rbegin()->first;
    }
    
    int minimum() {
        return s.begin()->first;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */