// O(n^2)的dp算法

const int maxn = 103, INF = 0x7f7f7f7f;
int a[maxn], f[maxn];
int n,ans = -INF;
int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++) 
    {
        scanf("%d", &a[i]);
        f[i] = 1;
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<i; j++)
            if(a[j] < a[i]) // 这里给为等号求解的就是最长不下降子序列
                f[i] = max(f[i], f[j]+1);
    for(int i=1; i<=n; i++) 
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}


// O(nlogn) 贪心和dp
const int INF=0x3f3f3f3f;  
int l=10, g[100], d[100], num[maxn];
 
int main()  
{  
    fill(g, g+l, INF);  
    int max_=-1;  
    for(int i=0; i<l; i++)  
    {  
        int j = lower_bound(g, g+l, num[i]) - g;  // 最长不下降子序列可使用upper_bound函数
        d[i] = j+1;  
        if(max_<d[i])  
            max_=d[i];  
        g[j] = num[i];  
    }  
    printf("%d\n", max_);  
    return 0;  
}  

// update 2024.9.17 LIS and LDS

// LIS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n; // 输入序列的长度
    cin >> n;
    vector<int> sequence(n);
    for(int i = 0; i < n; i++)
    {
        cin >> sequence[i];
    }

    vector<int> minTail; // 存储长度为 i+1 的上升子序列的最小可能尾部元素
    for(int i = 0; i < n; i++)
    {
        // 在 minTail 中找到第一个大于等于 sequence[i] 的位置
        auto it = lower_bound(minTail.begin(), minTail.end(), sequence[i]);
        if(it == minTail.end())
        {
            // 如果没有找到，说明 sequence[i] 可以作为一个新的最长子序列的尾部
            minTail.push_back(sequence[i]);
        }
        else
        {
            // 否则，用更小的值更新当前位置
            *it = sequence[i];
        }
    }

    // minTail 的长度即为最长严格上升子序列的长度
    cout << "最长严格上升子序列的长度为：" << minTail.size() << endl;
    return 0;
}


// LDS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n; // 输入序列的长度
    cin >> n;
    vector<int> sequence(n);
    for(int i = 0; i < n; i++)
    {
        cin >> sequence[i];
    }

    vector<int> maxTail; // 存储长度为 i+1 的下降子序列的最大可能尾部元素
    for(int i = 0; i < n; i++)
    {
        // 在 maxTail 中找到第一个小于等于 sequence[i] 的位置
        auto it = lower_bound(maxTail.begin(), maxTail.end(), sequence[i], greater<int>());
        if(it == maxTail.end())
        {
            // 如果没有找到，说明 sequence[i] 可以作为一个新的最长子序列的尾部
            maxTail.push_back(sequence[i]);
        }
        else
        {
            // 否则，用更大的值更新当前位置
            *it = sequence[i];
        }
    }

    // maxTail 的长度即为最长严格下降子序列的长度
    cout << "最长严格下降子序列的长度为：" << maxTail.size() << endl;
    return 0;
}

