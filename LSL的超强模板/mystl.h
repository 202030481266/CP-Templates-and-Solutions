#pragma once
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>        
#include <iostream>       
#include <iomanip>
#include <sstream>         
#include <stdexcept>
#include <algorithm>       
#include <cmath>           
#include <numeric>
#include <functional>
#include <complex>
#include <list>
#include <vector>         
#include <stack>
#include <queue>
#include <deque>          
#include <bitset>        
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <ctime>
#include <optional>
#include <cstdint>

using namespace std;


// 构造整数随机数据
// 梅森素数旋转算法
vector<int> get_random_data(size_t times, int lower, int upper) {
	mt19937 gen(random_device{}());
	uniform_int_distribution<int> u(lower, upper);
	vector<int> res;
	for (int i = 0; i < times; i++)
		res.emplace_back(u(gen));
	return res;
}
string get_random_alpha_string(size_t length) {
	auto index = get_random_data(length, 0, 25);
	string res;
	for (int i = 0; i < length; i++) res += char(index[i] + 'a');
	return res;
}
string get_random_digit_string(size_t length) {
	auto index = get_random_data(length, 0, 9);
	string res;
	for (int i = 0; i < length; i++) res += char(index[i] + '0');
	return res;
}

// get leetcode vector
string integerVectorToString(vector<int> list, int length = -1) {
	if (length == -1) {
		length = list.size();
	}
	if (length == 0) {
		return "[]";
	}
	string result;
	for (int index = 0; index < length; index++) {
		int number = list[index];
		result += to_string(number) + ", ";
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

