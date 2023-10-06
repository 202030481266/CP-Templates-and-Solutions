// https://leetcode.cn/problems/last-substring-in-lexicographical-order/
// 必然是一个最大的后缀，那么可以使用后缀数组暴力过掉，也可以使用双指针遍历优化过程。



struct SA {
	// 构造后缀数组, S是对应的字符串
	// N表示字符串的长度，M是对应的字母表大小
	// index from 1 to N
	string S;
	int N, M;
	vector<int> y, x, c, sa, rk, wt;

	SA() { N = M = 0; }
	SA(string s) {
		S = s;
		N = s.size();
		M = 122; // 小写字母的ASCII码对应的最大值
		y.resize(N + M + 1);
		x.resize(N + M + 1);
		c.resize(N + M + 1);
		sa.resize(N + M + 1);
		rk.resize(N + M + 1);
		wt.resize(30);
	}
	void SA_work() {
		// c数组就是个桶,先做一次最简单的基数排序
		// x[i]表示第i个后缀的第一个关键字
		for (int i = 1; i <= N; ++i) {
			x[i] = S[i - 1]; // 注意index的变化
			++c[x[i]];
		}
		for (int i = 2; i <= M; ++i) c[i] += c[i - 1];
		for (int i = N; i >= 1; --i) sa[c[x[i]]--] = i;
		// 倍增
		for (int k = 1; k <= N; k <<= 1) {
			int num = 0;
			// y[i]表示第二关键字排名为i的后缀，第一关键字的位置 
		    // 第n-k+1到第n位是没有第二关键字的 所以排名在最前面
			for (int i = N - k + 1; i <= N; ++i) y[++num] = i;
			// 按照排名来确定位置是为了后面的方便处理
			for (int i = 1; i <= N; ++i) if (sa[i] > k) y[++num] = sa[i] - k;
			// 桶清零初始化，就是为了使用第一关键字来进行排序
			for (int i = 1; i <= M; ++i) c[i] = 0;
			for (int i = 1; i <= N; ++i) ++c[x[i]];
			for (int i = 2; i <= M; ++i) c[i] += c[i - 1];
			// 根据第一关键字来进行确定排序，abccdd,比如我本来这里的d排名第五，但是因为第一关键字
			// 是c，所以我的排名就是c桶里面最大的,因为那个y数组是按排名来的，所以排名靠后的被优先
			// 处理了，（本质上就是已经处理了第二关键字），所以可以保证cd的排名比cc大。
			for (int i = N; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
			// 就是懒得存储变量，把没用的y数组先存储了现在的x数组
			swap(x, y);   // 关键的地方要理解，x表达的是第一关键字的意思
			x[sa[1]] = 1; // 排名第一的后缀第一关键字就是1，然后一次使用sa数组去更新
			num = 1;
			for (int i = 2; i <= N; ++i) {
				// 如果两个部分都是一样的，那么表明这两部分结合后应该有一样的排名,比如有abab
				// 就会在k=1的时候产生两个ab后缀，一个是sa[1],另一个对应的是sa[2]
				if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
					x[sa[i]] = num;
				else x[sa[i]] = ++num;
			}
			// 如果最后的排名等于N表明排序已经结束了
			if (num == N) break;
			M = num;
		}
	}
	vector<int> get_height() {
		// 获取最重要的高度数组，解题还的是靠这个玩意才行
		// LCP(i,j)为suff(sa[i])与suff(sa[j])的最长公共前缀
		/*
			LCP有几条重要的性质(证明过程建议去看博客，实际上并不是很难):
			1、LCP(i,k)=min(LCP(i,j),LCP(j,k)) 对于任意1<=i<=j<=k<=n
			2、LCP(i,k)=min(LCP(j,j-1)) 对于任意1<i<=j<=k<=n
			3、设height[i]为LCP(i,i-1)，1<i<=n，显然height[1]=0；
			4、设h[i]=height[rk[i]]，同样的，height[i]=h[sa[i]];
			5、可以得到h[i]>=h[i-1]-1;
			简单理解就是说比如对于一个后缀i-1，在它的排名前面的是后缀k，那么现在讨论后缀k+1和
			后缀i的关系。如果后缀k和后缀i-1的第一个字符不相同，那么很简单，此时两者的最长公共
			前缀就是0，height[rk[i-1]]=0。那么显然就是有height[rk[i]]>=height[rk[i-1]]-1成立。
			那么如果第一个字符相同呢？显然，此时肯定有后缀k+1排在后缀i前面，并且他们的LCP就是
			height[rk[i-1]]-1,并且显然的是和后缀i有最长LCP的一定是排名最靠近它的，也就是sa[rk[i]-1]
			因此后缀k+1和后缀i的最长前缀满足height[rk[i]]>=height[rk[i-1]]-1,也就是h[i]>=h[i-1]-1
		*/
		int k = 0;
		vector<int> height(N + 1);
		for (int i = 1; i <= N; ++i) rk[sa[i]] = i;
		for (int i = 1; i <= N; ++i) {
			if (rk[i] == 1) continue; // 最小的后缀的height为0
			if (k) --k;  // h[i]>=h[i-1]-1;
			int j = sa[rk[i] - 1];
			// 注意index的改变必须要减一
			while (j + k <= N && i + k <= N && S[i + k - 1] == S[j + k - 1]) ++k;
			height[rk[i]] = i; // h[i] = height[rk[i]]
		}
		return height;
	}
};

class Solution {
public:
    string lastSubstring(string s) {
    	// 字典序最大的子串
    	auto suf = new SA(s);
    	suf->SA_work();
    	int n = s.size();
    	int index = suf->sa[n];
    	return s.substr(index - 1, n - index + 1);
    }
};


// 双指针
class Solution {
public: 
	String lastSubstring(String s) {
        int length = s.length();
        int left = 0, right = 1, step = 0;
        while (right + step < length) {
            if (s.charAt(left + step) == s.charAt(right + step)) {
                step++;
            } else {
                if (s.charAt(left + step) < s.charAt(right + step)) {
                    left += step + 1;
                } else {
                    right += step + 1;
                }
                step = 0;
                right = Math.max(right, left + 1);
            }
        }
        return s.substring(left);
    }
}

