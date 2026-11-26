#include <bits/stdc++.h.>
using namespace std;


class Solution {
public:
    bool canAliceWin(int n) {
        if (n < 10) return false;
        int x = 10;
        int flag = 0;
        while (true) {
            if (n >= x) {
                n -= x;
                --x;
            }
            else {
                return flag ? true : false;
            }
            flag ^= 1;
        }
        return true;
    }
};
