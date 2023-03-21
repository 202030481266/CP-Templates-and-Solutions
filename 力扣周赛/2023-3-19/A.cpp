class Solution {
public:
    vector<int> evenOddBit(int n) {
        int odd = 0, even = 0;
        for (int i = 10; i >= 0; --i) {
            if (i & 1) {
                if ((n >> i) & 1) ++odd;
            }
            else {
                if ((n >> i) & 1) ++even;
            }
        }
        return vector<int>{even, odd};
    }
};