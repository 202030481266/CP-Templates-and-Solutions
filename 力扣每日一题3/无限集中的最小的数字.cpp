class SmallestInfiniteSet {
    int vis[1001];
public:
    SmallestInfiniteSet() {
        for (int i = 1; i <= 1000; ++i) vis[i] = 1;
    }
    
    int popSmallest() {
        for (int i = 1; i <= 1000; ++i) 
            if (vis[i]) {
                vis[i] = 0;
                return i;
            }
        return -1;
    }
    
    void addBack(int num) {
       vis[num] = 1;
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */