#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Constants
const int maxn = 1e6+7;

const int mod = 998244353;

// Precomputed factorials
long long factorials[maxn];

// Fenwick Tree (Binary Indexed Tree) implementation
class FenwickTree {
public:
    vector<int> tree;
    int n;

    FenwickTree(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    // Increase the value at position idx by delta
    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    // Get prefix sum up to position idx
    int query(int idx) {
        int result = 0;
        while (idx > 0) {
            result += tree[idx];
            idx -= idx & -idx;
        }
        return result;
    }
};

// Segment Tree implementation
class SegmentTree {
public:
    vector<int> tree;
    int n;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        build(1, 1, n);
    }

    // Build the tree
    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = 1;  // Initialize with 1
        } else {
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    // Update the tree: set the value at index idx to 0
    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node] = 0;  // Set count to 0
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid) {
                update(node * 2, l, mid, idx);
            } else {
                update(node * 2 + 1, mid + 1, r, idx);
            }
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    // Query the tree to find the k-th unused number
    int query(int node, int l, int r, int k) {
        if (l == r) {
            return l;
        } else {
            int mid = (l + r) / 2;
            if (tree[node * 2] >= k) {
                return query(node * 2, l, mid, k);
            } else {
                return query(node * 2 + 1, mid + 1, r, k - tree[node * 2]);
            }
        }
    }
};

// Calculate permutation rank using Fenwick Tree (Cantor expansion)
long long getPermutationRank(vector<int>& perm) {
    int n = perm.size();
    long long rank = 0;

    FenwickTree bit(n);
    // Initialize BIT with counts 1 for positions from 1 to n
    for (int i = 1; i <= n; i++) {
        bit.update(i, 1);
    }

    for (int i = 0; i < n; i++) {
        int x = perm[i];
        // Number of elements less than x that are still unused
        int smaller = bit.query(x - 1);
        rank = (rank + smaller * factorials[n - 1 - i] % mod) % mod;
        // Mark x as used
        bit.update(x, -1);
    }

    // Since permutation ranks start from 0, no need to add 1
    return rank;
}

// Recover permutation from rank using Segment Tree (inverse Cantor expansion)
vector<int> getPermutationFromRank(int n, long long rank) {
    vector<int> perm;

    SegmentTree segTree(n);

    for (int i = 0; i < n; i++) {
        long long fact = factorials[n - 1 - i];
        int index = rank / fact;
        rank %= fact;

        // index starts from 0, so k = index + 1
        int k = index + 1;
        int num = segTree.query(1, 1, n, k);
        perm.push_back(num);
        segTree.update(1, 1, n, num);
    }

    return perm;
}

// Main function example
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Precompute factorials
    int n;
    cin >> n;
    factorials[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorials[i] = factorials[i - 1] * i % mod;
    }

    // Example: Calculate the rank of permutation [2,1,3]
    // vector<int> perm = {2, 1, 3};
    // long long rank = getPermutationRank(perm);
    // cout << "Permutation [2,1,3] has rank: " << rank << endl;

    // Example: Recover permutation from rank
    // int n = 3;
    // long long testRank = 2;
    // vector<int> recoveredPerm = getPermutationFromRank(n, testRank);
    // cout << "Permutation corresponding to rank " << testRank << " is: ";
    // for (int x : recoveredPerm) {
    //     cout << x << " ";
    // }
    // cout << endl;

    vector<int> perm(n);
    for (int& v : perm) cin >> v;
    long long rank = getPermutationRank(perm);

    cout << rank+1 << endl;

    return 0;
}