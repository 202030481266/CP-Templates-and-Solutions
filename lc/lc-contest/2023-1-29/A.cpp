class Solution {
public:
    int distinctIntegers(int n) {
        unordered_set<int> hs;
        vector<int> a;

        auto f = [&]() {
            vector<int> b;
            for (auto c : a) {
                for (int i = 1; i <= n; ++i) 
                    if (c % i == 1) 
                        if (!hs.count(i)) b.emplace_back(i), hs.emplace(i);
            }
            if (b.size() == 0) return false;
            a = b;
            return true;
        };
        a.emplace_back(n);
        hs.emplace(n);
        while (f()) ;
        return hs.size();
    }
};