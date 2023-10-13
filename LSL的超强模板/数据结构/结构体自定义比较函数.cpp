struct Node
{
    int x,y;
    bool operator <(Node a) const  {  return y < a.y; }
    bool operator >(Node a) const  {  return y > a.y; }
};
priority_queue<Node> A;                    //大根堆
priority_queue<Node, vector<Node>, greater<Node> > B;    //小根堆 



// 标准库传递一个显示的 function 类型
auto cmp = [](const pair<int, int> a, const pair<int, int>b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q;