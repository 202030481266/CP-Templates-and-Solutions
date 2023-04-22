using namespace std;
// 最简单的ASCII哈希方法
int ascii_hash(string s) {
	int res = 0;
	for (int i = 0; i < s.size(); ++i) res += s[i] * (i + 1);
	return res;
}


// ELFHash，压缩非常密集，冲突很少，基本思想是使用数字的二进制来操作
static unsigned int ELFHash(string str) {
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;
	unsigned int len = str.length();
	for (i = 0; i < len; i++)
	{
		hash = (hash << 4) + (str[i]);
		if ((x = hash & 0xF0000000) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

// BKDRHash，基本思想就是把字符串当做一个seed进制数来处理 
static unsigned int BKDRHash(string str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();
	for (i = 0; i < len; i++)
	{
		hash = (hash * seed) + (str[i]);
	}
	return hash;
}

// Rabin-Karp算法，通过使用字符串哈希来加速算法去匹配字符串
static vector<int> SearchString(string A, string B) {
	vector<int> retVal;
	unsigned long siga = 0;
	unsigned long sigb = 0;
	unsigned long Q = 100007;
	unsigned long D = 256;
	int ALength = A.length();
	int BLength = B.length();

	for (int i = 0; i < BLength; ++i)
	{
		siga = (siga * D + (unsigned long)A[i]) % Q;
		sigb = (sigb * D + (unsigned long)B[i]) % Q;
	}

	if (siga == sigb)
		retVal.push_back(0);

	unsigned long pow = 1;

	for (int k = 1; k <= BLength - 1; ++k)
		pow = (pow * D) % Q;

	for (int j = 1; j <= ALength - BLength; ++j)
	{
		siga = (siga + Q - pow * (unsigned long)A[j - 1] % Q) % Q;
		siga = (siga * D + (unsigned long)A[j + BLength - 1]) % Q;

		if (siga == sigb)
			if (A.substr(j, BLength) == B)
				retVal.push_back(j);
	}

	return retVal;
}
// use example
/*
	string data = "the quick brown fox jumps over the lazy dog";
	vector<int> value = SearchString(data, "over"); // 26
*/