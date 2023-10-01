// 基础算法的头文件，包含了绝大多数的基础的算法的简明清晰的实现。
namespace mySort {
    // 归并排序的递归版本实现，通过使用归并排序还可以实现简单的逆序对计数
    // 对a中的[low,high)进行排序，性能在100000个数的情况下大约需要430ms
    // 而std::sort需要大概40ms，非常快！！非常牛逼！！
    void merge_sort(vector<int>& a, int low, int high) {
        if (high - low < 2)
            return;
        int mid = (low + high) >> 1;
        merge_sort(a, low, mid);
        merge_sort(a, mid, high);
        vector<int> b;
        // 赋值使用back_inserter是为了保证容器的容量不一致产生的错误
        // merge_sort的速度瓶颈在于这个数组值的复制导致大量的时间浪费
        copy(a.begin() + low, a.begin() + mid, back_inserter(b));
        for (int i = low, j = mid, k = 0; k < b.size(); i++) {
            if (j == high || b[k] <= a[j]) {
                a[i] = b[k++];
            }
            else {
                a[i] = a[j++]; //  ans+=(mid-i+1)就可以统计逆序对的个数
            }
        }
    }
    // 计数排序的实现(桶实现方法), 在随机数据100000的情况下用时平均4ms，吊打绝大多数排序算法
    // 但是这里注意不能让值域的方法太大，过大的值域不如使用标准排序。
    void counting_sort(vector<int>& a) {
        int max = *max_element(a.begin(), a.end());
        vector<int> cnt(max + 1);
        for (int x : a) {
            ++cnt[x];
        }
        for (int i = 1; i < cnt.size(); i++) {
            cnt[i] += cnt[i - 1];
        }
        int n = a.size();
        vector<int> b(n);
        // 这里的排序后的排名是从0开始的
        for (int i = n - 1; i >= 0; i--) {
            b[--cnt[a[i]]] = a[i];
        }
        a = b;
    }
    // 基数排序，也是使用桶排序的方法，需要比较多的空间切换，空间开销比较大，小范围不一定
    // 比std::sort更加优良，所以在大数情况下速度才有非常明显的提高。100000个数的情况下用时31ms
    void radix_sort(vector<int>& a) {
        int max_val = *max_element(a.begin(), a.end());
        // 进行单个位置上的桶排序
        int n = a.size();
        vector<int> b(n);
        function<void(int)> count_sort = [&](int exp) {
            vector<int> buckets(10, 0);
            // 把数据的位数上的数字放进桶里面进行统计
            for (int i = 0; i < n; i++) ++buckets[(a[i] / exp) % 10];
            for (int i = 1; i < 10; i++) buckets[i] += buckets[i - 1];
            // 相同于计数排序，计数排序的数字是按照从0开始逐渐到n-1的，为了保证后面的数有着更加后
            // 的排名，所以要倒序开始分配排名，这样可以保证排序的稳定性。
            for (int i = n - 1; i >= 0; i--) b[--buckets[(a[i] / exp) % 10]] = a[i];
            a = b;
        };
        for (int exp = 1; max_val / exp > 0; exp *= 10) count_sort(exp);
    }
    // 手写的快排程序，纯粹就是为了防止某些人问我（sort它不香吗）,100000个数的平均用时36ms
    void quick_sort(vector<int>& a, int l, int r) {
        int mid = a[(l + r) >> 1], i = l, j = r;
        do {
            while (a[i] < mid) ++i; // 查找第一个比mid大的数
            while (a[j] > mid) --j; // 查找第一个比mid小的数
            if (i <= j) {
                swap(a[i], a[j]); // 进行交换
                ++i, --j;
            }
        } while (i <= j);
        if (l < j) quick_sort(a, l, j); // 递归左区间
        if (i < r) quick_sort(a, i, r); // 递归右区间
    }
}


// 进制转换函数
// 先转换为十进制数字转换
string transform(int x, int y, string s) {
    string res = "";
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '-') continue;
        if (s[i] >= '0' && s[i] <= '9') {
            sum = sum * x + s[i] - '0';
        }
        else {
            sum = sum * x + s[i] - 'A' + 10;
        }
    }
    while (sum) {
        char tmp = sum % y;
        sum /= y;
        if (tmp <= 9) {
            tmp += '0';
        }
        else {
            tmp = tmp - 10 + 'A';
        }
        res = tmp + res;
    }
    if (res.length() == 0) res = "0";
    if (s[0] == '-') res = '-' + res;
    return res;
}