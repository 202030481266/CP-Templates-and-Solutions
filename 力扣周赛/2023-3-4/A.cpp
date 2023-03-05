class Solution {
public:
    int splitNum(int num) {
        vector<int> a;

        int x = num;
        while (x) {
            if (x % 10)
                a.emplace_back(x % 10);
            x /= 10;
        }
        sort(a.begin(), a.end());
        int n = 0, m = 0;
        for (int i = 0; i < a.size() && i + 1 < a.size(); i += 2) {
            // cerr << n << ' ' << m << endl;
            n = n * 10 + a[i];
            m = m * 10 + a[i + 1];
        }
        if (a.size() & 1)
            return min(n * 10 + m, m * 10 + n) + a.back();
        else 
            return n + m;
    }
};