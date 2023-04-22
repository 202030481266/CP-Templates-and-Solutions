struct Node
{
    int x,y;
    bool operator <(Node a) const  {  return y < a.y; }
    bool operator >(Node a) const  {  return y > a.y; }
};
priority_queue<Node> A;                    //大根堆
priority_queue<Node, vector<Node>, greater<Node> > B;    //小根堆 