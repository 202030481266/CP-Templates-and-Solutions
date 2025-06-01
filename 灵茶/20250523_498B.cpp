#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void cf498B() {
    int n, T, t;
    double p, ans = 0.0;
    
    cin >> n >> T;
    
    vector<double> f(T + 1, 0.0);
    f[0] = 1.0;
    
    for (int i = 1; i <= n; i++) {
        cin >> p >> t;
        p /= 100.0;
        
        double np = pow(1 - p, t - 1);
        double np2 = np * (1 - p);
        
        vector<double> nf(T + 1, 0.0);
        
        for (int j = i; j <= T; j++) {
            double d = 0.0;
            if (j > t) {
                d = f[j - t - 1] * np;
            }
            
            nf[j] = (nf[j - 1] - d) * (1 - p) + f[j - 1] * p;
            
            if (j >= t) {
                nf[j] += f[j - t] * np2;
            }
            
            ans += nf[j];
        }
        
        f = nf;
    }
    
    cout << fixed << setprecision(9) << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cf498B();
    return 0;
}