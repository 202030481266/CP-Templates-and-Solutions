#include <bits/stdc++.h>
using namespace std;

// 函数用于检查是否可以达到平均成绩mid
bool is_possible(double mid, int n, int k, const vector<int> &a, const vector<int> &b) {
    // 计算 c_i = a_i - (mid / 100) * b_i
    vector<double> c(n);
    for(int i = 0; i < n; ++i){
        c[i] = a[i] - (mid / 100.0) * b[i];
    }
    // 使用 nth_element 选择前 n - k 个最大的 c_i
    // 第 n - k 个元素的索引为 n - k - 1
    int select_count = n - k;
    if(select_count <= 0){
        // 如果允许放弃所有测试，平均成绩可以达到 100
        return true;
    }
    nth_element(c.begin(), c.begin() + select_count - 1, c.end(), greater<double>());
    // 计算前 n - k 个 c_i 的和
    double sum = 0.0;
    for(int i = 0; i < select_count; ++i){
        sum += c[i];
    }
    return sum >= -1e-9; // 考虑浮点数精度
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while(true){
        int n, k;
        cin >> n >> k;
        if(n == 0 && k == 0) break;
        vector<int> a(n), b(n);
        for(auto &x: a) cin >> x;
        for(auto &x: b) cin >> x;
        
        double l = 0.0, r = 100.0;
        // 二分查找的迭代次数足够多以确保精度
        for(int iter = 0; iter < 100; ++iter){
            double mid = (l + r) / 2.0;
            if(is_possible(mid, n, k, a, b)){
                l = mid;
            }
            else{
                r = mid;
            }
        }
        // 结果四舍五入
        double result = l;
        int final_result = round(result + 1e-8);
        cout << final_result << "\n";
    }
}