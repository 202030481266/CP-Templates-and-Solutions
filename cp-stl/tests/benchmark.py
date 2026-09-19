"""Compare template performance with an optional Git baseline; saves raw timings and medians."""
from pathlib import Path
import argparse
import csv
from datetime import datetime
import hashlib
import io
import json
import os
import platform
import shutil
import statistics
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
LIB = ROOT / "cp-stl"
BUILD = ROOT / ".build" / "benchmarks"
FLAGS = ["-std=c++17", "-O2", "-DNDEBUG", "-Wall", "-Wextra", "-Wshadow"]


def run(command, **kwargs):
    result = subprocess.run([str(arg) for arg in command], capture_output=True, **kwargs)
    if result.returncode:
        raise RuntimeError(result.stdout.decode("utf-8", "replace") +
                           result.stderr.decode("utf-8", "replace"))
    return result.stdout.decode("utf-8", "replace")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline", help="Git commit/tag to compare against (e.g. c250d4f)")
    parser.add_argument("--repeats", type=int, default=5, help="paired process runs (default: 5)")
    parser.add_argument("--compiler", help="GCC/Clang; defaults to VS Code compilerPath")
    args = parser.parse_args()
    if args.repeats < 1:
        parser.error("--repeats must be positive")
    settings = json.loads((ROOT / ".vscode/settings.json").read_text(encoding="utf-8-sig"))
    compiler = shutil.which(args.compiler or settings["C_Cpp.default.compilerPath"])
    if compiler is None:
        raise RuntimeError("Compiler not found; specify --compiler.")
    env = {**os.environ, "PATH": str(Path(compiler).parent) + os.pathsep + os.environ.get("PATH", "")}
    BUILD.mkdir(parents=True, exist_ok=True)
    includes = {"current": LIB}
    baseline_commit = None
    if args.baseline:
        baseline_commit = run(["git", "rev-parse", "--verify", args.baseline + "^{commit}"],
                              cwd=ROOT, timeout=30).strip()
        snapshot = BUILD / "baseline" / baseline_commit / "cp-stl"
        files = run(["git", "ls-tree", "-r", "--name-only", baseline_commit, "--", "cp-stl"],
                    cwd=ROOT, timeout=30).splitlines()
        for name in files:
            if not name.endswith(".hpp"):
                continue
            relative = Path(name).relative_to("cp-stl")
            target = snapshot / relative
            if not target.resolve().is_relative_to(snapshot.resolve()):
                raise RuntimeError("Invalid snapshot path")
            target.parent.mkdir(parents=True, exist_ok=True)
            content = subprocess.run(["git", "show", f"{baseline_commit}:{name}"], cwd=ROOT,
                                     capture_output=True, check=True, timeout=30).stdout
            target.write_bytes(content)
        if not snapshot.is_dir():
            raise RuntimeError("Baseline does not contain cp-stl headers")
        includes = {"baseline": snapshot, **includes}

    header_hashes = {
        path.relative_to(LIB).as_posix(): hashlib.sha256(
            path.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
        for path in sorted(LIB.rglob("*.hpp"))
    }
    benchmark_hash = hashlib.sha256((LIB / "tests/benchmarks.cpp").read_bytes().replace(
        b"\r\n", b"\n")).hexdigest()
    executables = {}
    for label, include in includes.items():
        directory = BUILD / label
        directory.mkdir(parents=True, exist_ok=True)
        executable = directory / ("benchmark.exe" if os.name == "nt" else "benchmark")
        run([compiler, *FLAGS, "-I", include, LIB / "tests/benchmarks.cpp",
             "-o", executable.name], cwd=directory, env=env, timeout=90)
        executables[label] = executable
    samples = {label: {} for label in executables}
    checksums = {}
    for trial in range(args.repeats):
        labels = list(executables)
        if trial & 1:
            labels.reverse()
        for label in labels:
            output = run([executables[label]], cwd=ROOT, env=env, timeout=60)
            for name, milliseconds, checksum in csv.reader(io.StringIO(output)):
                if name in checksums and checksums[name] != checksum:
                    raise RuntimeError(f"Checksum differs across versions/runs: {name}")
                checksums[name] = checksum
                samples[label].setdefault(name, []).append(float(milliseconds))
            print(f"Completed {trial + 1}/{args.repeats}: {label}", flush=True)
    if len({tuple(cases) for cases in samples.values()}) != 1:
        raise RuntimeError("Benchmark case lists differ")
    results = {}
    for name in checksums:
        result = {"checksum": checksums[name]}
        for label in executables:
            values = samples[label][name]
            if len(values) != args.repeats:
                raise RuntimeError(f"Missing samples: {label}/{name}")
            result[label] = {"median_ms": statistics.median(values),
                             "min_ms": min(values), "max_ms": max(values), "samples_ms": values}
        if "baseline" in result:
            result["speedup"] = result["baseline"]["median_ms"] / max(result["current"]["median_ms"], 1e-9)
        results[name] = result
        baseline_text = f"{result['baseline']['median_ms']:.3f} -> " if "baseline" in result else ""
        speedup_text = f" ({result['speedup']:.2f}x)" if "speedup" in result else ""
        print(f"{name}: {baseline_text}{result['current']['median_ms']:.3f} ms{speedup_text}")
    report = {
        "measured_at": datetime.now().astimezone().isoformat(timespec="seconds"),
        "baseline_commit": baseline_commit,
        "current_headers_sha256_lf": header_hashes,
        "benchmark_source_sha256_lf": benchmark_hash,
        "current_head": run(["git", "rev-parse", "HEAD"], cwd=ROOT, timeout=30).strip(),
        "working_tree": run(["git", "status", "--short"], cwd=ROOT, timeout=30),
        "compiler": run([compiler, "--version"], cwd=ROOT, env=env, timeout=30).splitlines()[0],
        "flags": FLAGS, "platform": platform.platform(), "processor": platform.processor(),
        "repeats": args.repeats, "seed": 20260919, "results": results,
    }
    output_path = BUILD / "results.json"
    output_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"Raw measurements: {output_path}")


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8")
    sys.stderr.reconfigure(encoding="utf-8")
    main()
