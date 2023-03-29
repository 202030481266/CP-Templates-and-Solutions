// https://leetcode.cn/problems/count-anagrams/



class Solution {
public:
	static constexpr int p = 1000000007;
	vector<string> split(const string& str, const string& delim) {  
		vector<string> res;  
		if("" == str) return res;  
		//先将要切割的字符串从string类型转换为char*类型  
		char * strs = new char[str.length() + 1] ; //不要忘了  
		strcpy(strs, str.c_str());   
	 
		char * d = new char[delim.length() + 1];  
		strcpy(d, delim.c_str());  
	 
		char *p = strtok(strs, d);  
		while(p) {  
			string s = p; //分割得到的字符串转换为string类型  
			res.push_back(s); //存入结果数组  
			p = strtok(NULL, d);  
		}  
	 
		return res;  
	} 
	long long quick_power(long long a, long long b) { 
	    long long ans = 1 % p;
	    for(; b; b >>= 1) {
	        if(b & 1) ans = ans * a % p;
	        a = a * a % p;
	    }
	    return ans;
	}
	// femat 
	long long inv(long long x) {
		return quick_power(x, p - 2) % p;
	}
    int countAnagrams(string s) {
    	auto words = split(s, " ");

    	int n = s.size();

    	vector<long long> fac(n + 1);
    	vector<long long> ifac(n + 1);
    	fac[0] = 1ll;
    	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % p;
    	ifac[n] = inv(fac[n]);
    	for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % p;

    	long long cur = 1;
    	vector<long long> cnt(26);
   		for (string w : words) {
   			fill(cnt.begin(), cnt.end(), 0);
   			for (char ch : w) ++cnt[ch - 'a'];
   			int m = w.size();
   			cur = cur * fac[m] % p;
   			for (int i = 0; i < 26; ++i) 
   				if (cnt[i] > 0) 
   					cur = cur * ifac[cnt[i]] % p;
   		}
   		return cur;
    }
};