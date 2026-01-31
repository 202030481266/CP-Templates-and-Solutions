template<typename T, uint32_t MAX_BIT = 32>
struct Trie {
    static const int B = MAX_BIT;
    struct node {
        node* nxt[2];
        int sz;
        node() {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    }* root;
    Trie() { root = new node(); }
    void insert(T val) {
        node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--) {
            int b = val >> i & 1;
            if (cur->nxt[b] == NULL)
                cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }
    void del(T val) {
        node* cur = root;
        cur->sz--;
        for (int i = B - 1; i >= 0; --i) {
            int b = val >> i & 1;
            if (cur->nxt[b]->sz == 1) {
                del(cur->nxt[b]);
                cur->nxt[b] = NULL;
                return;
            }
            cur = cur->nxt[b];
            cur->sz--;
        }
    }
    int query(T x, T k) { // number of values s.t. val ^ x < k
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (cur == NULL)
                break;
            int b1 = x >> i & 1, b2 = k >> i & 1;
            if (b2 == 1) {
                if (cur->nxt[b1])
                    ans += cur->nxt[b1]->sz;
                cur = cur->nxt[!b1];
            } else
                cur = cur->nxt[b1];
        }
        return ans;
    }
    T get_max(T x) { // returns maximum of val ^ x
        node* cur = root;
        T ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[!k])
                cur = cur->nxt[!k], ans <<= 1, ans++;
            else
                cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }
    T get_min(T x) { // returns minimum of val ^ x
        node* cur = root;
        T ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[k])
                cur = cur->nxt[k], ans <<= 1;
            else
                cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }
    void del(node* cur) { // 删除所有的位
        for (int i = 0; i < 2; i++)
            if (cur->nxt[i])
                del(cur->nxt[i]);
        delete (cur);
    }
};


int main() {
    Trie<int, 4> t;
    t.insert(1);
    t.insert(2);
    t.insert(4);
    t.insert(5);
    cout << t.get_max(8) << endl;
    t.del(5);
    cout << t.get_max(8) << endl;
    t.del(4);
    cout << t.get_max(8) << endl;
}