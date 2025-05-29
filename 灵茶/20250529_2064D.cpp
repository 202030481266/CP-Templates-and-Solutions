#include <bits/stdc++.h>
using namespace std;

/*
 * 一个数字不能和二进制长度大于自己的数字异或
 * 一个数字和二进制长度等于自己的数字的异或会减少二进制长度
 * 一个数字和二进制长度小于自己的数字异或不会改变自己的二进制长度
*/

void cf2064D() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, q;
        cin >> n >> q;
        
        vector<int> a(n);
        array<int, 31> pre;
        fill(pre.begin(), pre.end(), -1);
        
        vector<array<int, 31>> pres(n + 1);
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            int m = bit_width((uint32_t)a[i]);
            pres[i] = pre;
            pre[m] = i;
        }
        pres[n] = pre;
        
        vector<int> s(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            s[i] = s[i + 1] ^ a[i];
        }
        
        for (int query = 0; query < q; query++) {
            int x;
            cin >> x;
            int oriX = x;
            int cur = n, preM = 31, maxP = -1;
            
            while (true) {
                int m = bit_width((uint32_t)x);
                
                if (m + 1 < preM) {
                    int maxVal = -1;
                    for (int i = m + 1; i < preM; i++) {
                        maxVal = max(maxVal, pres[cur][i]);
                    }
                    maxP = max(maxP, maxVal);
                }
                
                int p = pres[cur][m];
                if (p <= maxP) {
                    cout << n - 1 - maxP << " ";
                    break;
                }
                
                x = oriX ^ s[p + 1];
                if (x < a[p]) { // 有可能会小于
                    cout << n - 1 - p << " ";
                    break;
                }
                
                x ^= a[p];
                preM = m + 1;
                cur = p;
            }
        }
        cout << "\n";
    }
}

int main() {
    cf2064D();
    return 0;
}