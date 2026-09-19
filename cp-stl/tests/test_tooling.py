"""Optional maintainer checks. Run: python cp-stl/tests/test_tooling.py
Daily VS Code build/run/export and the algorithm test task only need PowerShell + GCC.
"""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import json
import os
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[2]
LIB = ROOT / "cp-stl"
BUILD = ROOT / ".build" / "tooling"
BUILD.mkdir(parents=True, exist_ok=True)
PS = Path(os.environ["WINDIR"]) / "System32/WindowsPowerShell/v1.0/powershell.exe"
settings = json.loads((ROOT / ".vscode/settings.json").read_text(encoding="utf-8"))
COMPILER = Path(settings["C_Cpp.default.compilerPath"])
GDB = COMPILER.with_name("gdb.exe")
ENV = {**os.environ, "PATH": str(COMPILER.parent) + os.pathsep + os.environ["PATH"]}


def run(args, *, stdin=None, success=True, cwd=ROOT):
    result = subprocess.run(
        [str(x) for x in args], input=stdin, stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT, cwd=cwd, env=ENV, timeout=90,
    )
    text = result.stdout.decode("utf-8", errors="replace").replace("\r\n", "\n")
    if success and result.returncode:
        raise AssertionError(f"{args}\nexit={result.returncode}\n{text}")
    return result.returncode, text


def cp(action, source=None, *extra, root=ROOT, success=True):
    args = [PS, "-NoLogo", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File",
            root / "cp-stl/tools/cp.ps1", "-Action", action, "-Compiler", COMPILER]
    if source is not None:
        args += ["-Source", source]
    args += list(extra)
    return run(args, success=success, cwd=root)


def compile_header(path):
    source = f'#include "{path.relative_to(LIB).as_posix()}"\nint main() {{}}\n'
    run([COMPILER, "-std=c++17", "-Wall", "-Wextra", "-Werror",
         "-I", LIB, "-x", "c++", "-fsyntax-only", "-"], stdin=source.encode())


headers = sorted(LIB.rglob("*.hpp"))
with ThreadPoolExecutor(max_workers=3) as pool:
    list(pool.map(compile_header, headers))
print(f"PASS: {len(headers)} independently compiled C++17 headers", flush=True)

tasks = json.loads((ROOT / ".vscode/tasks.json").read_text(encoding="utf-8"))["tasks"]
launch = json.loads((ROOT / ".vscode/launch.json").read_text(encoding="utf-8"))["configurations"][0]
assert launch["preLaunchTask"] in {task["label"] for task in tasks}
assert all(task["type"] == "process" for task in tasks)
assert Path(launch["miDebuggerPath"]) == GDB
assert launch["sourceFileMap"]["${workspaceFolder}/.build/debug/main.cpp"]["useForBreakpoints"]
print("PASS: VS Code task/debug configuration consistency", flush=True)

for name in ["fenwick", "中文 路径/求和"]:
    source = LIB / "examples" / f"{name}.cpp"
    expected = source.with_suffix(".ans").read_text(encoding="utf-8")
    _, text = cp("Run", source, "-InputFile", source.with_suffix(".in"))
    assert text.endswith(expected), text
print("PASS: sample files, Chinese source paths, spaces and UTF-8 output", flush=True)

# Copy only the maintained library to exercise a workspace path containing shell
# metacharacters. No shell parses these paths; no recursive cleanup is performed.
copy_root = BUILD / "中文 工作区 [&] '"
assert copy_root.resolve().is_relative_to(BUILD.resolve())
shutil.copytree(LIB, copy_root / "cp-stl", dirs_exist_ok=True)
_, text = cp("Run", copy_root / "cp-stl/examples/中文 路径/求和.cpp",
             "-InputFile", copy_root / "cp-stl/examples/中文 路径/求和.in", root=copy_root)
assert text.endswith("总和：15\n"), text
print("PASS: workspace root with Chinese, spaces, brackets, ampersand and apostrophe", flush=True)

echo = BUILD / "echo.cpp"
echo.write_text('#include <iostream>\nint main() { std::cout << std::cin.rdbuf(); }\n', encoding="utf-8")
input_path = BUILD / "输入 [&].txt"
payload = "中文输入\n1 2 3\n"
input_path.write_text(payload, encoding="utf-8", newline="\n")
_, text = cp("Run", echo, "-InputFile", input_path)
assert text.endswith(payload), text
print("PASS: stdin redirection preserves UTF-8 bytes", flush=True)

# Compile the export without any project -I. A disabled conditional must not
# consume the guard of a header that is included again below.
source = BUILD / "expand.cpp"
source.write_text(
    '#include <iostream>\n'
    '#if 0\n#include "data_structures/dsu.hpp"\n#endif\n'
    '#include "data_structures/dsu.hpp"\n'
    '#include "dp/sequence.hpp"\n'
    'int main() { cp::DSU d(2); d.merge(0, 1); '
    'std::cout << d.size(0) << " " << cp::inversion_count(std::vector<int>{3, 1, 2}) << "\\n"; }\n',
    encoding="utf-8",
)
expanded = BUILD / "submission.cpp"
run([PS, "-NoProfile", "-ExecutionPolicy", "Bypass", "-File",
     LIB / "tools/expand.ps1", "-Source", source, "-Output", expanded])
standalone = BUILD / "standalone.exe"
run([COMPILER, "-std=c++17", expanded, "-o", standalone])
assert run([standalone])[1] == "2 2\n"
# Exercise the VS Code export action and LOCAL-only starter include too.
copy_source = copy_root / "cp-stl/template.cpp"
cp("Export", copy_source, root=copy_root)
run([COMPILER, "-std=c++17", copy_root / "submission.cpp", "-o", standalone])
assert run([standalone])[1] == ""
print("PASS: standalone export, transitive includes, conditional includes and starter", flush=True)

if (ROOT / "ac-library/atcoder/convolution").is_file():
    acl = BUILD / "acl.cpp"
    acl.write_text(
        '#include <iostream>\n#include <atcoder/convolution>\n'
        'int main(){auto c=atcoder::convolution(std::vector<int>{1,2},std::vector<int>{3,4});'
        'for(auto x:c)std::cout<<x<<" ";}\n', encoding="utf-8")
    run([PS, "-NoProfile", "-ExecutionPolicy", "Bypass", "-File",
         LIB / "tools/expand.ps1", "-Source", acl, "-Output", expanded])
    run([COMPILER, "-std=c++17", expanded, "-o", standalone])
    assert run([standalone])[1] == "3 10 8 "
    print("PASS: ACL expansion compiles without the external library", flush=True)

nonzero = BUILD / "exit7.cpp"
nonzero.write_text("int main() { return 7; }\n", encoding="utf-8")
assert cp("Run", nonzero, success=False)[0] == 7
bad = BUILD / "invalid.cpp"
bad.write_text("int main() { invalid syntax }\n", encoding="utf-8")
assert cp("Run", bad, success=False)[0] != 0
assert not (ROOT / ".build/release/program.exe").exists()
assert cp("Run", echo, "-InputFile", BUILD / "does-not-exist.in", success=False)[0] != 0
print("PASS: failure exit codes, missing input and no stale executable after failed compile", flush=True)

source = LIB / "examples/中文 路径/求和.cpp"
cp("Build", source, "-Mode", "Debug")
mirror = ROOT / ".build/debug/main.cpp"
assert mirror.read_bytes() == source.read_bytes()
_, text = run([GDB, "-batch", "-ex", "set charset UTF-8",
               "-ex", "break main.cpp:9", "-ex", "run", "-ex", "list",
               ROOT / ".build/debug/program.exe"])
assert "hit Breakpoint" in text and "std::cin >> n" in text, text
assert "No such file or directory" not in text, text
print("PASS: GDB source-line breakpoint and source listing for Chinese original file", flush=True)
print("All tooling checks passed.", flush=True)
