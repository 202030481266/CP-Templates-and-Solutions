/*
target: 找到序列中第k小的数字
complexity: O(n)
*/


int findKth(vector<int> a, int l ,int r,int k) {
    if (l == r) return a[l];
    
    int x = a[(l + r) >> 1] , i = l - 1 , j = r + 1;
    while (i < j) {
        while (a[++i] < x);
        while (a[--j] > x);
        if (i < j) swap(a[i] , a[j]);
    }
    //计算主元左边数字个数
    int lcnt = j - l + 1;
    //判断第k个数在左边还是右边
    if (k <= lcnt) return findKth(a, l, j, k);
    else return findKth(a, j + 1, r, k - lcnt);
}


// usage example
int main() {
	vector<int> a{1, 2, 3, 42, 52, 60, 78, 1, 23, 45};
	cout << findKth(a, 0, a.size() - 1, 10) << endl; // 78
}