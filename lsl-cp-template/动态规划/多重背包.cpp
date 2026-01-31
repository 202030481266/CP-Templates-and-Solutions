vector<int> Dp_multi(int T, vector<int> w, vector<int> v, vector<int> num) {
	// start from 1 to n
	// T 是总质量
	// num 是对应的物品个数

	// 使用二进制拆分把一组物品分成几个不一样的物品，把组这个概念拆掉
	auto W = w, V = v;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= num[i]; j <<= 1) {
			W.emplace_back(j * w[i]);
			V.emplace_back(j * v[i]);
			num[i] -= j;
		}
		if (num[i]) {
			W.emplace_back(num[i] * w[i]);
			V.emplace_back(num[i] * v[i]);
			num[i] = 0;
		}
	}
	// 01背包
	return Dp_01(T, W, V);
}

