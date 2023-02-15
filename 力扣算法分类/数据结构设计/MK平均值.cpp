// 动态维护长度为m的数列中的m-2*k个数字的平均值
// 技巧： 使用三个set有序集合来分别维护前k个数和后k个数以及中间的m-2*k个数字

class MKAverage {
private:
	queue<int> q;
	multiset<int> s1, s2, s3;
	long long sum;
	int m, k;;
public:
    MKAverage(int m, int k) {
    	this->m = m;
    	this->k = k;
    	sum = 0;
    }
    
    void addElement(int num) {
    	if (q.size() < m) {
    		q.push(num);
    		s2.emplace(num);
    		sum += num;
    		if (q.size() == m) {
    			while (s1.size() < k) {
    				s1.emplace(*s2.begin());
    				sum -= *s2.begin();
    				s2.erase(s2.begin());
    			}
    			while (s3.size() < k) {
    				s3.emplace(*s2.rbegin());
    				sum -= *s2.rbegin();
    				s2.erase(prev(s2.end()));
    			}
    		}
    		return;
    	} 
    	// should insert new element first
    	if (num < *s1.rbegin()) {
    		s1.emplace(num);
    		s2.emplace(*s1.rbegin());
    		sum += *s1.rbegin();
    		s1.erase(prev(s1.end()));
    	} else if (num > *s3.begin()) {
    		s3.emplace(num);
    		s2.emplace(*s3.begin());
    		sum += *s3.begin();
    		s3.erase(s3.begin());
    	} else {
    		s2.emplace(num);
    		sum += num;
    	}
    	// whatever it takes, s2 add one new element
    	// do the remove operation
		q.push(num);
		auto cur = q.front();
		q.pop();
		if (s1.count(cur) > 0) {
			s1.erase(s1.find(cur));
			s1.emplace(*s2.begin());
			sum -= *s2.begin();
			s2.erase(s2.begin());
	 	} else if (s3.count(cur) > 0) {
	 		s3.erase(s3.find(cur));
	 		s3.emplace(*s2.rbegin());
	 		sum -= *s2.rbegin();
	 		s2.erase(prev(s2.end()));
	 	} else {
	 		s2.erase(s2.find(cur));
	 		sum -= cur;
	 	}
    }
    
    int calculateMKAverage() {
    	if (q.size() < m) return -1;
    	else return sum / (m - 2 * k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */


// Splay树的做法，速度比STL快多了
#define INF 0x3f3f3f3f
#define ll long long

const int N = 1e5 + 5;

struct Node
{
    int s[2], p, v;
    int sz;
    ll sum;

    void init(int _v, int _p)
    {
        sum = v = _v, p = _p;
        sz = 1;
        s[0] = s[1] = 0;
    }
}tr[N];

int root, idx;

void pushup(int x)
{
    tr[x].sum = (ll)tr[tr[x].s[0]].sum + tr[tr[x].s[1]].sum + tr[x].v;
    tr[x].sz = tr[tr[x].s[0]].sz + tr[tr[x].s[1]].sz + 1;
}

void rotate(int x)  // 旋转
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k)  // splay操作
{
    while(tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if(z != k)
        {
            if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!k) root = x;
}

void insert(int v)
{
    int u = root, p = 0;
    while(u) p = u, u = tr[u].s[v > tr[u].v];

    u = ++idx;
    tr[u].init(v, p);
    if(p) tr[p].s[v > tr[p].v] = u;
    splay(u, 0);
    return;
}

void get_v(int v) // >=的最小数
{
    int u = root, res;
    while(u)
    {
        if(v <= tr[u].v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    splay(res, 0);
}

int getpn(int v, int f) // 0 prev 1 next
{
    get_v(v);
    int u = root;
    if(tr[u].v < v && !f) return u;
    if(tr[u].v > v && f) return u;
    u = tr[u].s[f];
    while(tr[u].s[f ^ 1]) u = tr[u].s[f ^ 1];
    return u;
}

void del(int v)
{
    int l = getpn(v, 0), r = getpn(v, 1);
    splay(l, 0), splay(r, l);
    tr[r].s[0] = 0;
}

int get_id_by_rank(int k)
{
    int u = root;
    while(1)
    {
        if(tr[tr[u].s[0]].sz >= k) u = tr[u].s[0];
        else if(tr[tr[u].s[0]].sz + 1 >= k) return u;
        else k -= tr[tr[u].s[0]].sz + 1, u = tr[u].s[1];
    }
}


class MKAverage
{
public:
    int m, k;
    queue<int> q;

    MKAverage(int m, int k) : m(m), k(k)
    {
        idx = root = 0;
        insert(INF), insert(-INF);
    }

    void addElement(int num)
    {
        q.push(num);
        insert(num);
        if(q.size() > m)
        {
            del(q.front());
            q.pop();
        }
    }

    int calculateMKAverage()
    {
        if(q.size() < m) return -1;
        else
        {
            int l = get_id_by_rank(k + 1), r = get_id_by_rank(m - k + 2);
            splay(l, 0), splay(r, l);
            return tr[tr[r].s[0]].sum / tr[tr[r].s[0]].sz;
        }
    }
};
