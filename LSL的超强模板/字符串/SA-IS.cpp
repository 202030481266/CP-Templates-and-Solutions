#include <bits/stdc++.h>
using namespace std;

void induced_sort(const vector<int>& vec, int val_range, vector<int>& SA, const vector<bool>& sl, const vector<int>& lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) {
        if (c + 1 < val_range) ++l[c + 1];
        ++r[c];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA) {
        if (i >= 1 && sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
    }
    fill(r.begin(), r.end(), 0);
    for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k]) {
        if (i >= 1 && !sl[i - 1]) {
            SA[--r[vec[i - 1]]] = i - 1;
        }
    }
}

vector<int> SA_IS(const vector<int>& vec, int val_range) {
    const int n = vec.size();
    vector<int> SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i) {
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
            new_lms_idx[k++] = SA[i];
        }
    }
    int cur = 0;
    SA[new_lms_idx[0]] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        bool same = true; 
        if (vec[i] != vec[j]) {
            same = false;
        }
        else {
            for (int a = i + 1, b = j + 1;; ++a, ++b) {
                if (vec[a] != vec[b]) {
                    same = false; 
                    break;
                }
                bool end_a = (!sl[a] && a > 0 && sl[a - 1]); 
                bool end_b = (!sl[b] && b > 0 && sl[b - 1]); 
                if (end_a || end_b) {
                    if (!(end_a && end_b)) same = false;
                    break;
                }
            }
        }
        if (!same) ++cur;
        SA[j] = cur;
    }

    for (size_t i = 0; i < lms_idx.size(); ++i)
        lms_vec[i] = SA[lms_idx[i]];

    if (cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        vector<int> sorted_lms_indices(lms_idx.size()); 
        for (size_t i = 0; i < lms_idx.size(); ++i) {
            sorted_lms_indices[i] = lms_idx[lms_SA[i]];         
        }
        new_lms_idx = sorted_lms_indices; 
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}

int main() {
    string s;
    cin >> s;
    vector<int> arr(s.size() + 1);
    copy(begin(s), end(s), begin(arr));
    arr.back() = '$';
    auto sa = SA_IS(arr, 128);
    sa.erase(sa.begin());
    for (int i = 0; i < sa.size(); ++i) {
        if (i < sa.size()) cout << sa[i]+1 << ' ';
        else cout << sa[i]+1 << endl;
    }
}