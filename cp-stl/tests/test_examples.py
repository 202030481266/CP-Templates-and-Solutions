"""Compile every usage example and check that its guide and output stay in sync."""
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
import argparse
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
LIB = ROOT / "cp-stl"
EXAMPLES = LIB / "examples"
GUIDES = LIB / "docs" / "usage"
BUILD = ROOT / ".build" / "examples"
FENCE = chr(96) * 3


def require(condition, message):
    if not condition:
        raise AssertionError(message)


def normalized(data):
    return data.replace(b"\r\n", b"\n")


def check_guide(source, guide):
    require(source.is_file(), f"Missing example: {source}")
    require(guide.is_file(), f"Missing usage guide: {guide}")
    answer = source.with_suffix(".ans")
    require(answer.is_file(), f"Missing expected output: {answer}")
    text = guide.read_text(encoding="utf-8")
    code = re.findall(FENCE + r"cpp\n(.*?)\n" + FENCE, text, re.S)
    output = re.findall(FENCE + r"text\n(.*?)\n" + FENCE, text, re.S)
    require(source.read_text(encoding="utf-8").rstrip("\n") in code,
            f"Guide code differs from example: {guide}")
    require(output and output[0] == answer.read_text(encoding="utf-8").rstrip("\n"),
            f"Guide stdout differs from expected output: {guide}")
    error = source.with_suffix(".err")
    if error.is_file():
        require(len(output) > 1 and output[1] == error.read_text(encoding="utf-8").rstrip("\n"),
                f"Guide stderr differs from expected output: {guide}")


def check_links(path):
    text = path.read_text(encoding="utf-8")
    text = re.sub(FENCE + r".*?" + FENCE, "", text, flags=re.S)
    for target in re.findall(r"\[[^\]]+\]\(([^)]+)\)", text):
        target = target.strip().strip("<>")
        if "://" in target or target.startswith("#"):
            continue
        target = target.split("#", 1)[0]
        require((path.parent / target).exists(), f"Broken link in {path}: {target}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", help="GCC/Clang executable; defaults to VS Code settings")
    parser.add_argument("--jobs", type=int, default=3, help="parallel compiler processes (default: 3)")
    args = parser.parse_args()
    require(args.jobs > 0, "--jobs must be positive")
    settings = json.loads((ROOT / ".vscode" / "settings.json").read_text(encoding="utf-8-sig"))
    configured = args.compiler or settings.get("C_Cpp.default.compilerPath", "g++")
    located = shutil.which(configured)
    require(located is not None, f"Compiler not found: {configured}")
    compiler = Path(located).resolve()
    env = os.environ.copy()
    env["PATH"] = str(compiler.parent) + os.pathsep + env.get("PATH", "")

    headers = sorted(LIB.rglob("*.hpp"))
    require(headers, "No template headers found")
    for header in headers:
        relative = header.relative_to(LIB)
        source = EXAMPLES / relative.with_suffix(".cpp")
        guide = GUIDES / relative.with_suffix(".md")
        check_guide(source, guide)
        require(f'#include "{relative.as_posix()}"' in source.read_text(encoding="utf-8"),
                f"Example must include its own template: {source}")
        require(f"cp-stl/docs/usage/{relative.with_suffix('.md').as_posix()}" in
                header.read_text(encoding="utf-8"), f"Missing guide pointer: {header}")
    check_guide(EXAMPLES / "template.cpp", GUIDES / "template.md")
    for path in [LIB / "README.md", EXAMPLES / "README.md", *GUIDES.rglob("*.md")]:
        check_links(path)
    print(f"PASS documentation: {len(headers)} template guides + starter guide", flush=True)

    def compile_and_run(source, local=True):
        relative = source.relative_to(EXAMPLES)
        directory = BUILD / relative.with_suffix("")
        directory.mkdir(parents=True, exist_ok=True)
        suffix = ".exe" if os.name == "nt" else ""
        executable = directory / ("program" + ("" if local else "-judge") + suffix)
        command = [str(compiler), "-std=c++17", "-O2", "-Wall", "-Wextra", "-Wshadow", "-Werror"]
        if local:
            command.append("-DLOCAL")
        command += ["-I", str(LIB), str(source), "-o", executable.name]
        compiled = subprocess.run(command, cwd=directory, env=env, capture_output=True, timeout=60)
        require(compiled.returncode == 0,
                f"Compile failed: {relative}\n{compiled.stdout.decode('utf-8', 'replace')}"
                f"{compiled.stderr.decode('utf-8', 'replace')}")
        input_file = source.with_suffix(".in")
        answer = source.with_suffix(".ans")
        require(answer.is_file(), f"Missing expected output: {answer}")
        result = subprocess.run([str(executable)], cwd=ROOT, env=env,
                                input=input_file.read_bytes() if input_file.is_file() else b"",
                                capture_output=True, timeout=10)
        require(result.returncode == 0,
                f"Run failed: {relative} ({result.returncode})\n"
                f"{result.stderr.decode('utf-8', 'replace')}")
        require(normalized(result.stdout) == normalized(answer.read_bytes()),
                f"stdout mismatch: {relative}\nExpected: {answer.read_bytes()!r}\n"
                f"Actual: {result.stdout!r}")
        error_file = source.with_suffix(".err")
        expected_error = error_file.read_bytes() if local and error_file.is_file() else b""
        require(normalized(result.stderr) == normalized(expected_error),
                f"stderr mismatch: {relative}\nExpected: {expected_error!r}\nActual: {result.stderr!r}")
        return relative.as_posix()

    sources = sorted(EXAMPLES.rglob("*.cpp"))
    failures = []
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = {pool.submit(compile_and_run, source): source for source in sources}
        for future in as_completed(futures):
            try:
                print(f"PASS {future.result()}", flush=True)
            except Exception as error:
                failures.append(f"{futures[future].relative_to(EXAMPLES)}: {error}")
    try:
        compile_and_run(EXAMPLES / "util" / "debug.cpp", local=False)
        print("PASS util/debug.cpp without LOCAL", flush=True)
    except Exception as error:
        failures.append(str(error))
    if failures:
        raise AssertionError("\n\n".join(failures))
    print(f"All {len(sources)} examples passed under GNU C++17, including expected stdout/stderr.")


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8")
    sys.stderr.reconfigure(encoding="utf-8")
    main()
