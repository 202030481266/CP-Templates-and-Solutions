// 二分查找

// 在单调递增的序列a中查找x的数中最小的一个，也就是x的后继。

while(l < r) { 
	int mid = (l + r) >> 1;
	if(a[mid] >= x) {
		r = mid;
	} else {
		l = mid + 1;
	}
}

// 在单调递增的序列a中查找x的数中最大的一个，也就是x的前驱。

while(l < r) {
	int mid = (l + r + 1) >> 1;
	if(a[mid] <= x) {
		l = mid;
	} else {
		r = mid - 1;
	}
}

// STL

s.lower_bound(a.begin(), a.end(), x); // 返回指向x的后继的迭代器
s.upper_bound(a.begin(), a.end(), x); // 返回指向>x的最小的一个元素的迭代器

// --------------------------------------------------------------

//  实数域上的二分

while(l + eps < r) { // eps是误差，通常为很小的常数
	double mid = (l + r) / 2;
	if(cal(mid)) {
		r = mid;
	} else {
		l = mid;
	}
}

// 或者直接循环固定次数好了:

for(int i = 0; i < 100; i++) {
	double mid = (l + r) / 2;
	if(cal(mid)) {
		r = mid;
	} else {
		l = mid;
	}
}

// ------------------------------------------------------------

//  二分答案最强的模板
while(l <= r) {
  int mid = (l + r) >> 1;
  if(check(mid)) ans = mid, r = mid - 1;
  else l = mid + 1;
}


// 查找最大的满足值

while(l < r) {
	int mid = (l + r) >> 1;
	if(valid(mid)) {
		l = mid;
	} else {
		r = mid - 1;
	}
}

// 查找最小的满足值

while(l < r) {
	int mid = (l + r) >> 1;
	if(valid(mid)) {
		r = mid;
	} else {
		l = mid + 1;
	}
}

// 闭区间的

while(l <= r) {
  int mid = (l + r) >> 1;
  if(check(mid)) {l = mid;}
  else r = mid;
}

// -----------------------------------------------------------

// 三分求单峰函数极值

while(fabs(r - l) >= eps) {
	double mid = (l + r) >> 1;
	if(cal(mid + eps) > cal(mid - eps)) {
		l = mid;
	} else {
		r = mid;
	}
}

//整数三分答案
int lv, rv;
while (l < r)
{
    int lm = l + (r - l) / 3;
    int rm = r - (r - l) / 3;
    lv = f(lm);
    rv = f(rm);
    if (lv < rv)
        l = lm + 1;
    else
        r = rm - 1;
}
ans = max(lv, rv);

//浮点三分答案
double lv, rv;
while (r - l > eps)
{
    double lm = l + (r - l) / 3;
    double rm = r - (r - l) / 3;
    lv = f(lm);
    rv = f(rm);
    if (lv < rv)
        l = lm;
    else
        r = rm;
}
ans = max(lv, rv);//浮点数的话lv,rv都可以