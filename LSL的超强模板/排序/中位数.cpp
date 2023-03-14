// 求解中位数，使用标准库的中位数

// nth_element 有两种调用方式
// nth_element(a,a+k,a+n)//默认的升序
// nth_element(a,a+k,a+n,cmp)//自定义比较方式
// 注：第k小/大是在[a,a+n)的范围内进行查找的
// 例如a[10]里面存放的是无序的数组元素，我们要从中找到第k小的数这时我们需要调用nth_element()函数，


// 1.找到第k小的数
// nth_element(a,a+k-1,a+10)//数组a是从0开始

// 2.当我们要找第k大的数是我们可以自定义比较方式
// nth_element(a,a+k-1，a+n,cmp)

// cmp还可以用于对vector，queue

// 注：nth_element 并没有对数组全部排序 仅仅只是找到了第k小的数并将其放到第k个位置上，（k之前的都比k小k之后的都比k大，但是并不是有序排列）




/*--------------------------动态维护中位数-------------------------*/

// 思路： 建立一个小根堆和一个大根堆，分别往两边添加元素，使得两边的堆的大小一致。
// 如果任何时候一个堆中的元素过多了，就把它移动到另一个堆中，此时中位数就是小根堆的堆顶。
// 对顶堆的思想。


// Runing Median
// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: running_median.cpp
# Author: xiaoshulin
# Created Time: 2022/5/12 17:19:13
#########################################################################*/
#include <bits/stdc++.h> 
using namespace std;

const int maxn = 1010;
priority_queue<int, vector<int>, greater<int>> q1; 
priority_queue<int, vector<int>, less<int>> q2; 
struct Node {int id; vector<int> res; } node[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t, n, id; cin >> t;
	while(t--) {
		cin >> id >> n;
		node[id].id = id;
		int median;
		for(int i = 1; i <= n; i++) {
			int temp;
			cin >> temp;
			if(i == 1) {
				node[id].res.push_back(temp);
				median = temp;
				q1.push(temp);
			} else {
				if(temp < median) q2.push(temp);
				else q1.push(temp);
				if(q1.size() > q2.size()) {
					while(q1.size() > q2.size() + 1) {
						int now = q1.top();
						q1.pop();
						q2.push(now);
					}
				}
				if(q2.size() > q1.size()) {
					while(q2.size() > q1.size()) {
						int now = q2.top();
						q2.pop();
						q1.push(now);
					}
				}
				if(i & 1) { median = q1.top(); node[id].res.push_back(median);}
			}
		}
		while(!q1.empty()) q1.pop();
		while(!q2.empty()) q2.pop();
	}
	for(int i = 1; i <= maxn; i++){
		if(node[i].id) {
			cout << i << ' ' << node[i].res.size() << endl;
			for(int k = 0; k < node[i].res.size(); k++) {
				if((k + 1) % 10 && k != node[i].res.size() - 1) cout << node[i].res[k] << ' ';
				else cout << node[i].res[k] << endl;
			}
		}
		else break;
	}
}


