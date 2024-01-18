#include <bits/stdc++.h>
using namespace std;




void test() {
	vector<long long> a(10);
	a[0] = a[1] = a[2] = 1;
	for (int i = 3; i <= 9; ++i) {
		for (int k = 1; k < i; ++k)
			a[i] += a[k] * a[i - k]; 
	}
	for (int i = 1; i <= 9; ++i) {
		cout << i <<  ' ' << a[i] << endl;
	}
}



int main() {
	test();
}
