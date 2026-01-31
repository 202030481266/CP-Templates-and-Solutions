#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<ll, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

struct Node { // long long 类型不然爆
    ll data;
    int idx;
    Node* prev, *next;
    Node(const ll& d, const int& id, Node* p = nullptr, Node* n = nullptr) : data(d), idx(id), prev(p), next(n) {}
};

class MergeList {
public:
    Node* head, *tail;
    MergeList(): head(nullptr), tail(nullptr) {}

    Node* add(Node* p, ll data, int id) {
        // 在节点 p 后插入一个节点，返回新插入的节点
        Node* newNode = new Node(data,id);
        if (!p) {
            head = tail = newNode;
        }
        else {
            newNode->prev = p;
            newNode->next = p->next;
            if (p->next) {
                p->next->prev = newNode;
            } else {
                tail = newNode;
            }
            p->next = newNode;
        }
        return newNode;
    }

    Node* merge(Node* p, Node* q, int id) {
        // 合并两个节点，返回新节点
        if (!p || !q) return nullptr;
        ll newData = p->data * q->data;
        Node* newNode = new Node(newData, id, p->prev, q->next);
        if (p->prev) {
            p->prev->next = newNode;
        } else {
            head = newNode;
        }
        if (q->next) {
            q->next->prev = newNode;
        } else {
            tail = newNode;
        }
        return newNode;
    }
};

struct cmp {
    bool operator () (const pair<Node*,Node*>& x, const pair<Node*, Node*>& y) const {
        return x.first->data*x.second->data > y.first->data*y.second->data;
    }
};

class Solution {
public:
    int minArrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        MergeList m;
        m.head = m.tail = new Node(-1, 0); //dummy node
        for (int i = 0; i < n; ++i) {
            m.add(m.tail, nums[i], i+1);
        }
        priority_queue<pair<Node*,Node*>, vector<pair<Node*,Node*>>, cmp> pq;
        Node* cur = m.head->next; // dummy node (head) -> first node -> second node -> ... -> tail
        while (cur && cur->next) {
            pq.push({cur,cur->next});
            cur = cur->next;
        }
        vector<bool> vis(n*2+1,false); // at most 2*n nodes
        int dfn = n+1;
        while (!pq.empty()) {
            auto [u, v] = pq.top();
            pq.pop();
            if (u->data*v->data > 1ll*k) break;
            if (vis[u->idx] || vis[v->idx]) continue;
            vis[u->idx] = vis[v->idx] = true;
            // u.prev u, v v.next
            Node* tmp = m.merge(u,v,dfn++);
            if (tmp->prev->data >= 0 && tmp->prev->data * tmp->data <= k) {
                pq.push({tmp->prev,tmp});
            }
            if (tmp->next && tmp->next->data * tmp->data <= k) {
                pq.push({tmp,tmp->next});
            }
        }
        int ans = 0;
        Node* p = m.head->next;
        while (p) {
            ++ans;
            p = p->next;
        }
        return ans;
    }
};