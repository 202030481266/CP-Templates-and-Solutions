class Solution {
public:
    map<long long, int> factorize(long long n) {
        map<long long, int> factors;
        for (int d = 2; (long long)d * d <= n; d++) {
            while (n % d == 0) {
                ++factors[d];
                n /= d;
            }
        }
        if (n > 1) {
            ++factors[n];
        }
        return factors;
    }
    int smallestValue(int n) {
        auto t = factorize(n), last = -1;
        while (t.size() > 1 || t.begin()->second > 1) {
            long long temp = 0;
            for (auto c = t.begin(); c != t.end(); c++) temp += (c->first * c->second);
            if (temp == last) return temp;
            else last = temp;
            t = factorize(temp);
        } 
        return t.begin()->first;
    }
};