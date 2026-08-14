#include <vector>
#include <numeric>
using namespace std;

// 计算阶乘
int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

// 康托展开:传入 1~n 的排列,返回哈希值 [0, n!-1]
int cantorExpand(const vector<int>& perm) {
    int n = perm.size();
    int hash = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0; // 第 i 位后面比 perm[i] 小的元素个数
        for (int j = i + 1; j < n; ++j) {
            if (perm[j] < perm[i]) cnt++;
        }
        hash += cnt * factorial(n - 1 - i);
    }
    return hash;
}

vector<int> cantorUnExpand(int hash, int n) {
    vector<int> elements(n);
    iota(elements.begin(), elements.end(), 1); // {1,2,...,n}
    vector<int> perm;
    for (int i = n; i >= 1; --i) {
        int f = factorial(i - 1);
        int idx = hash / f;
        hash %= f;
        perm.push_back(elements[idx]);
        elements.erase(elements.begin() + idx);
    }
    return perm;
}