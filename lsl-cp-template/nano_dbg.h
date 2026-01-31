//
// Created by 12584 on 2025/9/23.
//

#ifndef CLION_PROJECT_DBG_H
#define CLION_PROJECT_DBG_H

#endif //CLION_PROJECT_DBG_H

#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>
#include <array>
#include <string>
#include <utility>
#include <type_traits>
#include <bitset>

namespace dbg {
    // 输出流，默认为cerr
    std::ostream &out = std::cerr;

    // 前向声明
    template<typename T>
    void print(const T &val);

    template<typename T, typename... Args>
    void print(const T &first, const Args &... args);

    // 类型特征检测
    template<typename T, typename = void>
    struct is_pair : std::false_type {
    };

    template<typename T1, typename T2>
    struct is_pair<std::pair<T1, T2> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_tuple : std::false_type {
    };

    template<typename... Args>
    struct is_tuple<std::tuple<Args...> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_map : std::false_type {
    };

    template<typename K, typename V>
    struct is_map<std::map<K, V> > : std::true_type {
    };

    template<typename K, typename V>
    struct is_map<std::unordered_map<K, V> > : std::true_type {
    };

    template<typename K, typename V>
    struct is_map<std::multimap<K, V> > : std::true_type {
    };

    template<typename K, typename V>
    struct is_map<std::unordered_multimap<K, V> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_set : std::false_type {
    };

    template<typename V>
    struct is_set<std::set<V> > : std::true_type {
    };

    template<typename V>
    struct is_set<std::unordered_set<V> > : std::true_type {
    };

    template<typename V>
    struct is_set<std::multiset<V> > : std::true_type {
    };

    template<typename V>
    struct is_set<std::unordered_multiset<V> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_queue : std::false_type {
    };

    template<typename V>
    struct is_queue<std::queue<V> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_stack : std::false_type {
    };

    template<typename V>
    struct is_stack<std::stack<V> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_priority_queue : std::false_type {
    };

    template<typename V, typename Container, typename Compare>
    struct is_priority_queue<std::priority_queue<V, Container, Compare> > : std::true_type {
    };

    template<typename T, typename = void>
    struct is_container : std::false_type {
    };

    template<typename T>
    struct is_container<T, std::void_t<
                decltype(std::begin(std::declval<T>())),
                decltype(std::end(std::declval<T>())),
                typename T::value_type
            > > : std::true_type {
    };

    // string不作为容器处理
    template<>
    struct is_container<std::string> : std::false_type {
    };

    template<>
    struct is_container<std::wstring> : std::false_type {
    };

    // 打印pair
    template<typename T1, typename T2>
    void print_impl(const std::pair<T1, T2> &p) {
        out << "(";
        print(p.first);
        out << ", ";
        print(p.second);
        out << ")";
    }

    // 打印tuple辅助
    template<typename Tuple, std::size_t... I>
    void print_tuple_impl(const Tuple &t, std::index_sequence<I...>) {
        out << "(";
        std::size_t n = 0;
        ((print(std::get<I>(t)), out << (++n != sizeof...(I) ? ", " : "")), ...);
        out << ")";
    }

    // 打印tuple
    template<typename... Args>
    void print_impl(const std::tuple<Args...> &t) {
        if constexpr (sizeof...(Args) == 0) {
            out << "()";
        } else {
            print_tuple_impl(t, std::index_sequence_for<Args...>{});
        }
    }

    // 打印容器
    template<typename Container>
    void print_container(const Container &c) {
        out << "[";
        bool first = true;
        for (const auto &elem: c) {
            if (!first) out << ", ";
            first = false;
            print(elem);
        }
        out << "]";
    }

    // 打印map
    template<typename Map>
    void print_map(const Map &m) {
        out << "{";
        bool first = true;
        for (const auto &[key, val]: m) {
            if (!first) out << ", ";
            first = false;
            print(key);
            out << ": ";
            print(val);
        }
        out << "}";
    }

    // 打印set
    template<typename Set>
    void print_set(const Set &s) {
        out << "{";
        bool first = true;
        for (const auto &elem: s) {
            if (!first) out << ", ";
            first = false;
            print(elem);
        }
        out << "}";
    }

    // 打印queue
    template<typename T>
    void print_impl(std::queue<T> q) {
        out << "Queue[front -> ";
        bool first = true;
        while (!q.empty()) {
            if (!first) out << ", ";
            first = false;
            print(q.front());
            q.pop();
        }
        out << " <- back]";
    }

    // 打印priority_queue
    template<typename T, typename Container, typename Compare>
    void print_impl(std::priority_queue<T, Container, Compare> pq) {
        out << "PQ[";
        bool first = true;
        while (!pq.empty()) {
            if (!first) out << ", ";
            first = false;
            print(pq.top());
            pq.pop();
        }
        out << "]";
    }

    // 打印stack
    template<typename T>
    void print_impl(std::stack<T> s) {
        std::vector<T> temp;
        while (!s.empty()) {
            temp.push_back(s.top());
            s.pop();
        }
        out << "Stack[top -> ";
        bool first = true;
        for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
            if (!first) out << ", ";
            first = false;
            print(*it);
        }
        out << " <- bottom]";
    }

    // 打印bitset
    template<std::size_t N>
    void print_impl(const std::bitset<N> &b) {
        out << "0b" << b.to_string();
    }

    // 打印C数组
    template<typename T, std::size_t N>
    void print_impl(const T (&arr)[N]) {
        out << "[";
        for (std::size_t i = 0; i < N; ++i) {
            if (i > 0) out << ", ";
            print(arr[i]);
        }
        out << "]";
    }

    // 打印std::array
    template<typename T, std::size_t N>
    void print_impl(const std::array<T, N> &arr) {
        out << "[";
        for (std::size_t i = 0; i < N; ++i) {
            if (i > 0) out << ", ";
            print(arr[i]);
        }
        out << "]";
    }

    // 主打印函数
    template<typename T>
    void print(const T &val) {
        // bitset
        if constexpr (std::is_same_v<std::decay_t<T>, std::bitset<1> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<8> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<16> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<32> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<64> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<128> > ||
                      std::is_same_v<std::decay_t<T>, std::bitset<256> >) {
            print_impl(val);
        }
        // pair
        else if constexpr (is_pair<std::decay_t<T> >::value) {
            print_impl(val);
        }
        // tuple
        else if constexpr (is_tuple<std::decay_t<T> >::value) {
            print_impl(val);
        }
        // queue
        else if constexpr (is_queue<std::decay_t<T> >::value) {
            print_impl(val);
        }
        // stack
        else if constexpr (is_stack<std::decay_t<T> >::value) {
            print_impl(val);
        }
        // priority_queue
        else if constexpr (is_priority_queue<std::decay_t<T> >::value) {
            print_impl(val);
        }
        // map类
        else if constexpr (is_map<std::decay_t<T> >::value) {
            print_map(val);
        }
        // set类
        else if constexpr (is_set<std::decay_t<T> >::value) {
            print_set(val);
        }
        // std::array
        else if constexpr (std::is_array_v<std::remove_reference_t<T> >) {
            print_impl(val);
        }
        // 其他容器
        else if constexpr (is_container<std::decay_t<T> >::value) {
            print_container(val);
        }
        // 基本类型和string
        else {
            out << val;
        }
    }

    // 打印多个参数
    template<typename T, typename... Args>
    void print(const T &first, const Args &... args) {
        print(first);
        out << " ";
        print(args...);
    }

    // 带换行的打印
    template<typename... Args>
    void println(const Args &... args) {
        print(args...);
        out << std::endl;
    }

    // 打印二维vector
    template<typename T>
    void print_matrix(const std::vector<std::vector<T> > &matrix) {
        out << "Matrix " << matrix.size() << "x" << (matrix.empty() ? 0 : matrix[0].size()) << ":\n";
        for (const auto &row: matrix) {
            out << "  ";
            print(row);
            out << "\n";
        }
    }

    // 打印带标签的变量
    template<typename T>
    void print_var(const std::string &name, const T &val) {
        out << name << " = ";
        print(val);
        out << std::endl;
    }

    // 简化的调试函数
    template<typename... Args>
    void debug(const Args &... args) {
        println(args...);
    }
} // namespace dbg

#endif // DEBUG_PRINT_H

/* 使用示例:
 
主要API：

dbg::print(...) - 打印任意数量的参数（不换行）
dbg::println(...) - 打印任意数量的参数并换行
dbg::print_var("name", variable) - 打印变量名和值
dbg::print_matrix(matrix) - 专门打印二维矩阵
dbg::debug(...) - println 的别名

---

#include "debug_print.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 基本类型
    int a = 42;
    double b = 3.14;
    dbg::print_var("a", a);
    dbg::print_var("b", b);

    // STL容器
    vector<int> v = {1, 2, 3, 4, 5};
    dbg::println("vector:", v);

    // pair和tuple
    pair<int, string> p = {1, "hello"};
    tuple<int, double, string> t = {10, 3.14, "world"};
    tuple<int, int, int, int> t4 = {1, 2, 3, 4};
    dbg::println("Pair:", p);
    dbg::println("Tuple:", t);
    dbg::println("Tuple4:", t4);

    // map
    map<string, int> mp = {{"a", 1}, {"b", 2}, {"c", 3}};
    dbg::println("Map:", mp);

    // 嵌套容器
    vector<pair<int, int>> vp = {{1,2}, {3,4}, {5,6}};
    dbg::println("Vector of pairs:", vp);

    // 二维数组
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    dbg::print_matrix(matrix);

    // queue, stack, priority_queue
    queue<int> q;
    q.push(1); q.push(2); q.push(3);
    dbg::println("Queue:", q);

    stack<int> stk;
    stk.push(1); stk.push(2); stk.push(3);
    dbg::println("Stack:", stk);

    priority_queue<int> pq;
    pq.push(3); pq.push(1); pq.push(2);
    dbg::println("Priority Queue:", pq);

    // set
    set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};
    dbg::println("Set:", s);

    // array
    array<int, 5> arr = {1, 2, 3, 4, 5};
    dbg::println("Array:", arr);

    // C数组
    int carr[] = {10, 20, 30, 40};
    dbg::println("C array:", carr);

    return 0;
}

*/
