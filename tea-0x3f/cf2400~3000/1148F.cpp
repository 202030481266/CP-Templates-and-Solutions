#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> val(n);
    vector<long long> mask(n);
    long long S = 0;

    for (int i = 0; i < n; ++i) {
        cin >> val[i] >> mask[i];
        S += val[i]; // 计算初始总和
    }

    long long s = 0;

    for (int k = 0; k < 62; ++k) {
        long long sum_k = 0;
        
        for (int i = 0; i < n; ++i) {
            if ((mask[i] >> k) == 1) {
                sum_k += val[i];
            }
        }

        bool need_flip = false;
        if (S > 0 && sum_k > 0) need_flip = true;
        if (S < 0 && sum_k < 0) need_flip = true;

        if (need_flip) {
            s |= (1LL << k);
            for (int i = 0; i < n; ++i) {
                if ((mask[i] >> k) & 1) {
                    val[i] = -val[i];
                }
            }
        }
    }

    cout << s << "\n";
    return 0;
}