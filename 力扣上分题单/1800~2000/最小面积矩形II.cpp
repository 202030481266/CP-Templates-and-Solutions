// https://leetcode.cn/problems/minimum-area-rectangle-ii/
// 计算几何问题，挺有意思的


// 超时的枚举方法，有点祭
class Solution {
public:
	static constexpr double eps = 1e-7;
	double minAreaFreeRect(vector<vector<int>>& points) {
		auto cal = [&](pair<double, double> x, pair<double, double> y) {
			return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
		};
		auto check = [&](vector<double> points) -> pair<bool, double> {
			assert(points.size() == 8);
			pair<double, double> p1 = { points[0], points[1] };
			pair<double, double> p2 = { points[2], points[3] };
			pair<double, double> p3 = { points[4], points[5] };
			pair<double, double> p4 = { points[6], points[7] };
			double x = (p1.first + p2.first + p3.first + p4.first) / 4;
			double y = (p1.second + p2.second + p3.second + p4.second) / 4;
			pair<double, double> mid = { x, y };
			double d1 = cal(p1, mid), d2 = cal(p2, mid), d3 = cal(p3, mid), d4 = cal(p4, mid);
			if (fabs(d1 - d2) < eps && fabs(d2 - d3) < eps && fabs(d3 - d4) < eps) {
				double area = 0;
				double d5 = cal(p1, p2), d6 = cal(p1, p3), d7 = cal(p1, p4);
				if (d5 + d6 - 4 * d1 < eps) area = sqrt(d5) * sqrt(d6);
				else if (d5 + d7 - 4 * d1 < eps) area = sqrt(d5) * sqrt(d7);
				else area = sqrt(d6) * sqrt(d7);
				return { true, area };
			}
			return { false, 0 };
		};
		int n = points.size();
		double ans = 0;
		vector<int> use;
		function<void(int, int)> dfs = [&](int p, int d) {
			if (d == 5) {
				vector<double> temp;
				for (auto u : use) {
					temp.emplace_back(1.0 * points[u][0]);
					temp.emplace_back(1.0 * points[u][1]);
				}
				auto result = check(temp);
				if (result.first) {
					if (fabs(ans) < eps) ans = result.second;
					else ans = min(ans, result.second);
				}
				return;
			}
			for (int i = p; i < n; ++i) {
				use.emplace_back(i);
				dfs(i + 1, d + 1);
				use.pop_back();
			}
		};
		dfs(0, 1);
		return ans;
	}
};

// 大佬的AC方法，使用实数哈希
/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: O(n^2)
If you find this solution helpful, plz give a star:)
***************************************************/
typedef unsigned long long ull;
const double inf=1e10;
double ans;
namespace Hash{
	typedef unsigned int uint;
	const uint S=10,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,t;
		double y;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(uint x,double y){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){
				ans=min(ans,y-p->y); p->y=y;
				return;
			}
		p->t=T; p->x=x; p->y=y;
	}
	#undef H
} using namespace Hash;
inline uint h1(double x){ull t=*((ull*)&x); return (t>>32)^(t>>17);}
class Solution {
public:
	double minAreaFreeRect(vector<vector<int>>& p) {
		int n=p.size(); ans=inf; ++T;
		sort(p.begin(),p.end());
		for (int i=0;i<n;++i){
			uint x1=p[i][0],y1=p[i][1];
			for (int j=i+1;j<n;++j)if (p[j][1]>y1){
				uint x2=p[j][0],y2=p[j][1];
				double l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),t=(double)(x2-x1)/(y2-y1),d=x1*t+y1;
				insert(h1(l*3.14159+t*1.2345+d),l*sqrt(x1*x1+(y1-d)*(y1-d)));
			}
		}
		return ans==inf?0:ans;
	}
};
