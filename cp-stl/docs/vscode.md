# 在 Windows / VS Code 中写 C++

## 第一次使用

用 VS Code **打开整个仓库文件夹** `D:/CP-Templates-and-Solutions`。配置在仓库根目录的 `.vscode`，只打开一个 cpp 文件或单独打开 `cp-stl` 不会使用同一套配置。

本机已检查到：

- GCC 15.2.0：`C:/msys64/ucrt64/bin/g++.exe`
- GDB：`C:/msys64/ucrt64/bin/gdb.exe`
- Microsoft C/C++ 扩展：`ms-vscode.cpptools`

仓库设置已覆盖原先指向 `D:/mingw64/bin/g++.exe` 的用户设置。编译、IntelliSense 和调试使用 MSYS2 UCRT64 工具链；这种组合也是 [VS Code 官方 MinGW 指南](https://code.visualstudio.com/docs/cpp/config-mingw) 中的配置方式。

1. 执行一次 `Developer: Reload Window`，让工作区设置重新加载。
2. 打开 [中文路径示例](<../examples/中文 路径/求和.cpp>)。
3. 按 **Ctrl+Shift+B**，终端会编译并等待输入。
4. 粘贴下面两行并回车，应看到 `总和：15`：

```text
5
1 2 3 4 5
```

新题：新建 `scratch/main.cpp`，输入 `cpstart`，从补全列表选择起手模板；或者复制 [template.cpp](../template.cpp)。`scratch/` 已忽略，可以放心放临时解答。

## 每天只需要这几个操作

| 操作 | 入口 |
| --- | --- |
| 编译并交互运行当前 cpp | **Ctrl+Shift+B** |
| 设置 / 取消断点 | **F9**，或点击行号左侧 |
| 编译并断点调试 | **F5**，选择 `CP: Debug current file` |
| 单步越过 / 进入 / 继续 | F10 / F11 / F5 |
| 从样例文件读取输入 | `Tasks: Run Task → CP: Run with input.txt` |
| 生成可提交的单文件 | `Tasks: Run Task → CP: Export submission.cpp` |
| 测试模板 | `Tasks: Run Task → CP: Test templates` |
| 检查编译器和调试器 | `Tasks: Run Task → CP: Check environment` |

运行和调试前让 **cpp 文件成为当前活动编辑器**。F5 的源码映射也使用当前文件。不要在 `tasks.json`、`.hpp` 或只有 `class Solution`、没有 `main()` 的 LeetCode 片段上启动任务；要在本地测试这类片段，先加 `main()` 和构造数据。

程序的输入在下方 **Terminal（终端）**，不是 Output 或 Debug Console。程序等待输入时并没有卡死。Ctrl+C 可终止运行；以 EOF 结束输入的程序在 Windows 终端中可尝试 Ctrl+Z 后回车，或直接使用样例文件。

这些任务使用仓库自带配置。其他扩展的“Run Code”按钮可能执行另一套命令；日常固定用上表的入口即可。

## 从 input.txt 读取样例

在仓库根目录创建 UTF-8 的 `input.txt`，粘贴题目输入。然后回到解答 cpp，执行 `CP: Run with input.txt`。

快速体验树状数组例子：复制 [fenwick.in](../examples/fenwick.in) 为根目录 `input.txt`，打开 [fenwick.cpp](../examples/fenwick.cpp)，运行上述任务，预期输出：

```text
15
19
13
```

脚本直接把文件字节送入程序 stdin；不会经过 PowerShell 的字符串管道。建议保存为 **UTF-8（无 BOM）**，并保证样例确实符合题目输入格式。

程序工作目录统一为仓库根目录，所以自己写的 `ifstream("input.txt")` 也在根目录找文件。不要在将要提交的代码中忘记删除固定的本地文件重定向。

## 中文路径为什么现在能用

已经实测了中文文件名、中文子目录、空格，以及包含中文、空格、方括号、`&` 和单引号的仓库根目录的**编译与运行**。

- VS Code 任务使用 `type: process` 和独立参数，避免把文件名拼成 shell 命令。
- 文件、终端和编译器统一使用 UTF-8。
- 链接器在构建目录内生成英文的 `program.exe`，避免某些 Windows 链接器无法打开含中文的绝对输出路径。
- F5 编译时保留原文件的头文件相对路径和编译错误位置，单独把调试信息中的源文件名映射到 `.build/debug/main.cpp`。该文件是自动生成的镜像；VS Code 通过 `sourceFileMap` 显示原文件，**始终编辑原 cpp**。
- 任务使用系统自带的 Windows PowerShell 5.1，带 `-NoProfile`，避免个人 PowerShell 启动脚本影响编译；执行策略参数只作用于该次任务进程。

调试映射依据 [VS Code 官方 sourceFileMap 配置](https://code.visualstudio.com/docs/cpp/launch-json-reference#_sourcefilemap)。当前英文仓库根目录下，中文源文件的 GDB 行断点和源码读取已经测试通过。包含中文的仓库根目录测试覆盖编译、运行；F5 的完整 VS Code 界面操作尚未自动化验证，保留当前根目录路径即可使用已验证的 GDB 路径方案。

## 提交到 OJ

本地解答可以写：

```cpp
#include "data_structures/fenwick.hpp"
```

普通 OJ 没有你的本地文件。保持解答 cpp 为活动文件，执行 `CP: Export submission.cpp`，提交根目录生成的 `submission.cpp`。它会覆盖上一次导出，不覆盖解答。

导出器支持常规的 `#include "xxx.hpp"`、相对头文件和 `#include <atcoder/...>`；对依赖头文件递归展开，保留条件编译。它不是完整 C++ 预处理器：不展开宏生成的 include，也不会执行生成代码。起手模板的 LOCAL 调试输出在普通 OJ 构建中自动关闭。

`submission.cpp`、`input.txt`、`scratch/`、`.build/` 和可执行文件均已加入忽略规则，示例的 `.in`、`.ans` 和共享 `.vscode` 配置仍可提交。

## 换电脑、换编译器或语言标准

当前电脑无需重复安装。如果换电脑：

1. 按 [官方 MSYS2 安装步骤](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain) 安装 UCRT64 GCC 与 GDB，再安装 Microsoft C/C++ 扩展。
2. 修改 `.vscode/settings.json` 的 `C_Cpp.default.compilerPath`。
3. 修改 `.vscode/launch.json` 的 `miDebuggerPath`；同步两个文件中终端/调试的 PATH，使其指向同一工具链的 bin。
4. 执行 `CP: Check environment`。

语言标准只需修改 `C_Cpp.default.cppStandard`（例如 `c++17`、`c++20`、`c++23`），编译任务会读取同一个值。新模板支持 GNU C++17；旧题解若用了更高版本的功能，按代码要求调整。

Release 运行使用 `-O2 -g`；调试使用 `-Og -g3`，二者都有 `-Wall -Wextra -Wshadow -DLOCAL -D_GLIBCXX_ASSERTIONS`。可执行文件在 `.build/release` 和 `.build/debug`。同一模式共用一个当前程序，结束一次运行后再启动下一题，避免正在运行的 exe 被占用。

## 不经过 VS Code 的命令

在仓库根目录的 PowerShell 中：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File cp-stl/tools/cp.ps1 -Action Run -Source "cp-stl/examples/fenwick.cpp" -InputFile "cp-stl/examples/fenwick.in"
powershell -NoProfile -ExecutionPolicy Bypass -File cp-stl/tools/cp.ps1 -Action Test
powershell -NoProfile -ExecutionPolicy Bypass -File cp-stl/tools/cp.ps1 -Action Export -Source "scratch/main.cpp"
```

编译失败会删除旧的同模式可执行文件并返回失败，程序非零退出码也会向任务传递。遇到报错优先看终端第一条编译错误；不再出现“编译失败却运行了上一次程序”的情况。
