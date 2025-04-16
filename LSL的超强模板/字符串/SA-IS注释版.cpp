#include <bits/stdc++.h>
using namespace std;


void induced_sort(const vector<int>& vec, int val_range, vector<int>& SA, const vector<bool>& sl, const vector<int>& lms_idx) {
    // 1. 初始化并计算桶边界
    vector<int> l(val_range, 0), r(val_range, 0); // l: 桶的左边界, r: 桶的右边界
    // 统计每个字符出现的次数
    for (int c : vec) {
        if (c + 1 < val_range) ++l[c + 1]; // l[c+1] 累加 vec 中 <= c 的字符数（为计算左边界做准备）
        ++r[c]; // r[c] 累加 vec 中 == c 的字符数
    }
    // 计算前缀和，得到每个字符桶的精确边界
    partial_sum(l.begin(), l.end(), l.begin()); // l[c] 变为字符 c 的桶的起始位置 (L型后缀用)
    partial_sum(r.begin(), r.end(), r.begin()); // r[c] 变为字符 c 的桶的结束位置 (S型后缀用，开区间)

    // 2. 将 LMS 后缀放入桶中 (逆序扫描)
    fill(SA.begin(), SA.end(), -1); // 初始化 SA，-1 表示空位
    // 从后向前遍历 lms_idx (LMS 后缀索引列表)
    // LMS 后缀是 S 型，应该放在其对应字符桶的 *末尾*
    for (int i = lms_idx.size() - 1; i >= 0; --i) {
        int lms_pos = lms_idx[i]; // 当前 LMS 后缀的起始位置
        int char_val = vec[lms_pos]; // LMS 后缀的首字符
        // --r[char_val] 先将右边界减 1，然后将 LMS 后缀索引放入该位置
        SA[--r[char_val]] = lms_pos;
    }
    // 逆序扫描 lms_idx 是为了保证：如果多个 LMS 子串有相同首字符，它们在桶中能保持 lms_idx 中的相对顺序（虽然这一步 lms_idx 未必有序，但这是为后续递归后第二轮诱导排序的稳定性做准备）

    // 3. 诱导排序 L 型后缀 (正序扫描 SA)
    // L 型后缀应该放在其对应字符桶的 *开头*
    for (int i : SA) { // 遍历当前 SA 数组 (从左到右)
        // i 是 SA 中已经放置好的某个后缀的起始索引
        if (i >= 1 && sl[i - 1]) { // 如果 i > 0 且后缀 i-1 是 L 型 (sl[i-1] == true)
            int prev_pos = i - 1; // L 型后缀的起始位置
            int char_val = vec[prev_pos]; // L 型后缀的首字符
            // l[char_val]++ 先用当前的左边界 l[char_val] 放置，然后将左边界加 1
            SA[l[char_val]++] = prev_pos;
        }
    }
    // 正序扫描 SA 保证了 L 型后缀是按照字典序被放入桶中的。因为当扫描到 SA[k]=i 时，如果 i-1 是 L 型，那么 i-1 应该比所有以相同字符开头且已经被放入桶的 L 型后缀都要小（或者说，在字典序上更早出现）。

    // 4. 诱导排序 S 型后缀 (逆序扫描 SA)
    // 重新计算右边界 (因为 l 在上一步被修改了，虽然 r 没变，但为了清晰和可能存在的代码修改，这里重新计算)
    fill(r.begin(), r.end(), 0);
    for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    // S 型后缀（*非 LMS* 的 S 型）应该放在其对应字符桶的 *末尾*
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k]) { // 从后向前遍历 SA 数组
        // i = SA[k] 是当前扫描到的后缀的起始索引
        if (i >= 1 && !sl[i - 1]) { // 如果 i > 0 且后缀 i-1 是 S 型 (sl[i-1] == false)
            // 注意：LMS 后缀也是 S 型，但它们在步骤 2 中已经被精确放置了。
            // 这里的 S 型后缀是那些 *非 LMS* 的 S 型后缀。
            int prev_pos = i - 1; // S 型后缀的起始位置
            int char_val = vec[prev_pos]; // S 型后缀的首字符
            // --r[char_val] 先将右边界减 1，然后将 S 型后缀索引放入该位置
            SA[--r[char_val]] = prev_pos;
        }
    }
    // 逆序扫描 SA 保证了 S 型后缀是按照字典序被放入桶中的。因为当从后向前扫描到 SA[k]=i 时，如果 i-1 是 S 型，那么 i-1 应该比所有以相同字符开头且已经被放入桶的 S 型后缀都要大（或者说，在字典序上更晚出现），所以放在桶内更靠前的位置（因为是从桶尾部开始放）。
}


vector<int> SA_IS(const vector<int>& vec, int val_range) {
    const int n = vec.size();
    vector<int> SA(n);       // 最终的后缀数组
    vector<int> lms_idx;     // 存储 LMS 后缀的起始索引 (按位置升序)
    vector<bool> sl(n);      // 存储每个后缀的类型 (true: L-type, false: S-type)

    // 1. 分类后缀类型 (S/L) 并找到 LMS 后缀
    sl[n - 1] = false; // 定义最后一个后缀 ($) 为 S 型
    for (int i = n - 2; i >= 0; --i) {
        // 判断规则：
        // 1. vec[i] > vec[i+1] -> L 型
        // 2. vec[i] < vec[i+1] -> S 型
        // 3. vec[i] == vec[i+1] -> 与后缀 i+1 类型相同
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        // 找到 LMS (Left-Most S-type) 后缀：
        // 条件：后缀 i+1 是 S 型 (!sl[i+1]) 且后缀 i 是 L 型 (sl[i])
        // 此时 i+1 是一个 LMS 字符的位置
        if (sl[i] && !sl[i + 1]) {
            lms_idx.push_back(i + 1);
        }
    }
    // 因为是从后往前找的，所以需要反转得到按索引升序的 LMS 位置列表
    reverse(lms_idx.begin(), lms_idx.end());

    // 2. 第一次诱导排序：对 LMS 后缀进行排序
    // 这次排序的目标是确定 LMS 后缀之间的相对顺序
    // 输入的 lms_idx 是按位置排序的，induced_sort 会将这些 LMS 后缀初步放入 SA 数组中
    induced_sort(vec, val_range, SA, sl, lms_idx);

    // 3. 构造递归子问题
    // a. 提取排序后的 LMS 后缀索引
    vector<int> new_lms_idx(lms_idx.size()); // 存储排序后的 LMS 后缀索引
    vector<int> lms_vec(lms_idx.size());    // 存储缩减问题的输入向量 (LMS 子串的 "名称" 或 "排名")
    for (int i = 0, k = 0; i < n; ++i) {
        // 遍历 SA 数组，找到所有 LMS 后缀的位置
        // 判断 SA[i] 是否是 LMS 后缀的起始位置
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) { // S 型且前一个是 L 型
             new_lms_idx[k++] = SA[i]; // 收集排序后的 LMS 后缀索引
        }
    }

    // b. 计算 LMS 子串的 "名称" (排名)
    // 目的是判断哪些 LMS 子串是相同的，给它们赋予相同的排名/名称
    // 使用 SA 数组临时存储每个 LMS 后缀对应的排名
    int cur = 0; // 当前的排名
    SA[new_lms_idx[0]] = cur; // 第一个 LMS 子串排名为 0
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1]; // 上一个 LMS 后缀的起始位置
        int j = new_lms_idx[k];     // 当前 LMS 后缀的起始位置

        // 比较从 i 和 j 开始的两个 LMS 子串是否相同
        bool same = true; // 假设它们相同
        if (vec[i] != vec[j]) { // 首字符不同，肯定不同
            same = false;
        } 
        else {
            // 首字符相同，逐个比较后续字符，直到遇到下一个 LMS 字符或字符不同
            int a = i + 1, b = j + 1;
            while (true) {
                if (vec[a] != vec[b]) { // 字符不同
                    same = false;
                    break;
                }
                // 判断是否到达 LMS 子串的末尾 (即遇到下一个 LMS 字符)
                bool end_a = (!sl[a] && sl[a - 1]);
                bool end_b = (!sl[b] && sl[b - 1]);
                if (end_a || end_b) {
                    // 如果一个结束了，另一个没结束，或者都结束了
                    // 只有当两者 *同时* 结束时，才算相同 (same 保持 true)
                    // 否则，它们不同 (same 设为 false)
                    if (!(end_a && end_b)) {
                        same = false;
                    }
                    break; // 结束比较
                }
                ++a; ++b;
            }
        }
        // 根据比较结果更新排名
        if (!same) ++cur;
        SA[j] = cur; // 将排名存储在 SA[j] 位置 (临时)
    }

    // c. 构建缩减问题的输入向量 lms_vec
    // lms_vec[p] = 排名(第 p 个 LMS 后缀)
    // 这里 p 是按照 LMS 后缀在原串中的 *位置顺序* (lms_idx)
    for (size_t i = 0; i < lms_idx.size(); ++i) {
        lms_vec[i] = SA[lms_idx[i]]; // 从临时存储中取出排名
    }

    // 4. 递归求解子问题
    // 如果排名数量 cur+1 小于 LMS 后缀数量，说明有重复的 LMS 子串，需要递归解决
    if (cur + 1 < (int)lms_idx.size()) {
        // 递归调用 SA_IS，输入是排名向量 lms_vec，值范围是 cur+1
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        // 递归返回的是 lms_vec 的后缀数组 lms_SA
        // lms_SA[i] 表示排名第 i 小的 LMS 子串对应在 lms_vec 中的索引 p
        // 我们需要的是原串中的索引，即 lms_idx[p]
        // 所以，根据 lms_SA 重排 new_lms_idx
        vector<int> sorted_lms_indices(lms_idx.size()); // 临时存一下
        for (size_t i = 0; i < lms_idx.size(); ++i) {
            sorted_lms_indices[i] = lms_idx[lms_SA[i]];
        }
        new_lms_idx = sorted_lms_indices; // 更新 new_lms_idx 为真正排序好的 LMS 索引
    }
    // else (cur + 1 == lms_idx.size()): 所有 LMS 子串都不同，第一次诱导排序后的 new_lms_idx 就是最终排好序的 LMS 索引，无需递归。

    // 5. 第二次诱导排序：得到最终的 SA
    // 使用 *真正排好序* 的 LMS 后缀索引列表 (new_lms_idx) 进行最后一次诱导排序
    // 这次诱导排序会精确地确定所有后缀的最终位置
    induced_sort(vec, val_range, SA, sl, new_lms_idx);

    // 6. 返回最终的后缀数组
    return SA;
}