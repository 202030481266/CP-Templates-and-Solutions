class StockPrice {
    multiset<int> s;
    unordered_map<int, int> h;
    int mx;
public:
    StockPrice() {
        mx = 0;
    }
    
    void update(int timestamp, int price) {
        if (h.count(timestamp)) {
            auto it = s.lower_bound(h[timestamp]);
            s.erase(it);
        }
        h[timestamp] = price;
        s.insert(price);
        mx = max(mx, timestamp);
    }

    int current() {
        return h[mx];
    }
    
    int maximum() {
        return *s.rbegin();
    }
    
    int minimum() {
        return *s.begin();
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