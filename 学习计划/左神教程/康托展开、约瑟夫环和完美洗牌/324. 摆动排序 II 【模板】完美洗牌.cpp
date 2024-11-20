#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 快速选择算法 + 完美洗牌
class Solution {
private:
    static const int MAXN = 20;
    vector<int> start = vector<int>(MAXN);
    vector<int> split = vector<int>(MAXN);
    int size;
    int first, last;

    void swap(vector<int>& arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void partition(vector<int>& arr, int l, int r, int x) {
        first = l;
        last = r;
        int i = l;
        while (i <= last) {
            if (arr[i] == x) {
                i++;
            } else if (arr[i] < x) {
                swap(arr, first++, i++);
            } else {
                swap(arr, i, last--);
            }
        }
    }

    int randomizedSelect(vector<int>& arr, int n, int i) {
        int ans = 0;
        for (int l = 0, r = n - 1; l <= r;) {
            partition(arr, l, r, arr[l + rand() % (r - l + 1)]);
            if (i < first) {
                r = first - 1;
            } else if (i > last) {
                l = last + 1;
            } else {
                ans = arr[i];
                break;
            }
        }
        return ans;
    }

    void reverse(vector<int>& arr, int l, int r) {
        while (l < r) {
            swap(arr, l++, r--);
        }
    }

    void rotate(vector<int>& arr, int l, int m, int r) {
        reverse(arr, l, m);
        reverse(arr, m + 1, r);
        reverse(arr, l, r);
    }

    void build(int n) {
        size = 0;
        for (int s = 1, p = 2; p <= n; s *= 3, p = s * 3 - 1) {
            start[++size] = s;
            split[size] = p;
        }
    }

    int to(int i, int l, int r) {
        if (i <= (l + r) >> 1) {
            return i + (i - l + 1);
        } else {
            return i - (r - i + 1);
        }
    }

    void circle(vector<int>& arr, int l, int r, int i) {
        for (int j = 1; j <= i; j++) {
            int init = l + start[j] - 1;
            int cur = init;
            int next = to(cur, l, r);
            int curv = arr[cur];
            while (next != init) {
                int nextv = arr[next];
                arr[next] = curv;
                curv = nextv;
                cur = next;
                next = to(cur, l, r);
            }
            arr[init] = curv;
        }
    }

    void shuffle(vector<int>& arr, int l, int r) {
        int n = r - l + 1;
        build(n);
        for (int i = size; n > 0;) {
            if (split[i] <= n) {
                int m = (l + r) / 2;
                rotate(arr, l + split[i] / 2, m, m + split[i] / 2);
                circle(arr, l, l + split[i] - 1, i);
                l += split[i];
                n -= split[i];
            } else {
                i--;
            }
        }
    }

public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        randomizedSelect(nums, n, n / 2);
        if ((n & 1) == 0) {
            shuffle(nums, 0, n - 1);
            reverse(nums, 0, n - 1);
        } else {
            shuffle(nums, 1, n - 1);
        }
    }
};