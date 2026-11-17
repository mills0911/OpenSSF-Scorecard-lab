#!/usr/bin/env python3
"""Analyze production C++ sources with Clang Static Analyzer.

Clang may return exit status zero even when it reports analyzer warnings.
Use machine-readable plist diagnostics to make those findings fail CI.
"""

import os
import plistlib
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SOURCES = ("main.cpp", "BST.cpp", "node.cpp")


def main() -> int:
    clang = os.environ.get("CLANGXX", "clang++")
    reported = 0
    with tempfile.TemporaryDirectory(prefix="bst-clang-analyzer-") as directory:
        for source in SOURCES:
            report = Path(directory) / f"{source}.plist"
            command = [
                clang,
                "--analyze",
                "-std=c++20",
                "-Wall", "-Wextra", "-Wpedantic", "-Werror",
                "-I", str(ROOT),
                "-Xclang", "-analyzer-output=plist",
                "-o", str(report),
                str(ROOT / source),
            ]
            try:
                result = subprocess.run(command, cwd=ROOT, check=False, capture_output=True, text=True)
            except FileNotFoundError:
                print(f"Cannot run {clang}: install Clang and retry.", file=sys.stderr)
                return 2
            if result.stdout:
                print(result.stdout, end="")
            if result.stderr:
                print(result.stderr, end="", file=sys.stderr)
            if result.returncode != 0 or not report.exists():
                print(f"Clang analysis failed for {source}.", file=sys.stderr)
                return 1
            with report.open("rb") as stream:
                diagnostics = plistlib.load(stream).get("diagnostics", [])
            reported += len(diagnostics)
            for finding in diagnostics:
                message = finding.get("description", "Unspecified analyzer finding")
                print(f"{source}: {message}", file=sys.stderr)
            print(f"{source}: {len(diagnostics)} analyzer finding(s)")
    if reported:
        print(f"FAIL: {reported} static analyzer finding(s) require review.", file=sys.stderr)
        return 1
    print("PASS: Clang Static Analyzer reported no findings.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
