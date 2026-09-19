# 开始写题：template.cpp

[起手式源码](../../template.cpp) · [完整求和示例](../../examples/template.cpp) · [使用手册索引](README.md)

`template.cpp` 提供输入输出设置、常用整数别名和本地调试开关。复制它到自己的 `.cpp` 文件，在 `solve()` 中写一组数据的解法；它本身的 `solve()` 是空的。

## 使用顺序

1. 在仓库根目录新建 `scratch/main.cpp`，复制起手式，或输入 `cpstart` 选择代码片段。
2. 在 `solve()` 内读入数据、求解、输出答案。需要算法时添加对应的 `#include "类别/模板.hpp"`。
3. 默认只有一组数据。题目开头明确给出组数 `t` 时，才打开 `cin >> t;`；多组数据的容器通常在 `solve()` 内创建。
4. 打开自己的 `.cpp`，按 `Ctrl+Shift+B` 编译运行。提交前执行任务 `CP: Export submission.cpp`，提交生成的单文件。

## 完整例子

下面读入 `n` 个整数并求和。与其他模板的内置数据示例不同，这个例子需要标准输入。

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

#ifdef LOCAL
#include "util/debug.hpp"
#else
#define debug(...) ((void)0)
#endif

void solve() {
    int n;
    if (!(cin >> n)) return;
    i64 answer = 0;
    for (int i = 0; i < n; ++i) {
        i64 x;
        cin >> x;
        answer += x;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;  // 题目开头有测试组数时再打开。
    while (t--) solve();
    return 0;
}
```

### 示例输入

```input
5
1 2 3 4 5
```

### 预期标准输出

```text
15
```

在仓库根目录运行并自动读取输入文件：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File cp-stl/tools/cp.ps1 -Action Run -Source cp-stl/examples/template.cpp -InputFile cp-stl/examples/template.in
```

也可以在 VS Code 中运行后向终端粘贴上面的两行输入。计算过程为 `1+2+3+4+5=15`。

## 常用部分如何改

| 部分 | 用法 |
| --- | --- |
| `solve()` | 放一组数据的完整解法；多组测试时避免遗留上组状态。 |
| `i64` | `long long` 的别名，适合整数求和、距离等；仍需确保不溢出。 |
| `u64` | 无符号 64 位整数，常用于位运算；不用于表示负数。 |
| `i128` | GCC/Clang 扩展的 128 位整数；`cout` 不直接支持它，需要自行转换输出。 |
| `debug(...)` | 仓库本地任务定义 `LOCAL` 时输出到标准错误；普通 OJ 编译未定义 `LOCAL` 时不输出。详见 [debug](util/debug.md)。 |
| `ios::sync_with_stdio(false)` | 加速 C++ 流；启用后统一使用 `cin/cout`，避免混用 `scanf/printf`。 |
| `cin.tie(nullptr)` | 取消输入前自动刷新输出；交互题按需使用 `flush`。 |

`bits/stdc++.h` 和 `__int128_t` 面向 GNU/Clang 竞赛环境。这个例子在 GNU C++17 下验证，仓库默认编译为 C++20；VS Code 的编译器与中文路径配置见 [运行说明](../vscode.md)。
