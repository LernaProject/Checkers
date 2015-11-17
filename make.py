#!/usr/bin/env python3

import argparse
import contextlib
import os
import shlex
import subprocess
import sys

EXTENSIONS = {
    ".c": "C",
    ".cpp": "C++",
    ".cxx": "C++",
    ".cc": "C++",
    ".d": "D",
}

COMPILERS = {
    "C": """
        gcc {src} -o {bin} -O2
        -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion -Wcast-qual -Wcast-align
        -Wlogical-op -Wredundant-decls
        -Wno-unused-result -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-long-long
    """,
    "C++": """
        g++ {src} -o {bin} -O2
        -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -Wlogical-op
        -Wredundant-decls
        -Wno-unused-result -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-long-long
        # -Wuseless-cast -Wconversion
    """,
    "D": """
        dmd -release -inline -boundscheck=off -O {src} -od{out_dir}
    """,
}

def process(source, output_dir, force=False, quiet=False):
    name, ext = os.path.splitext(source)
    binary = os.path.join(os.path.split(source)[0], output_dir, name)
    if sys.platform.startswith("win"):
        binary += ".exe"
    lang = EXTENSIONS.get(ext)
    if quiet and lang is None:
        return True

    print("Processing", source, end="... ", flush=True)
    if lang is None:
        print("Unknown file type!", flush=True)
        return False

    assert lang in COMPILERS

    if not force and os.path.isfile(binary) and os.stat(binary).st_mtime > os.stat(source).st_mtime:
        print("Up-to-date", flush=True)
        return True

    source = shlex.quote(source)
    binary = shlex.quote(binary)
    cmd = COMPILERS[lang].format(src=source, bin=binary, out_dir=output_dir)
    cmd = shlex.split(cmd, comments=True)
    ret_code = subprocess.call(cmd)
    if ret_code != 0:
        return False
    print("Done.", flush=True)
    return True

def main():
    parser = argparse.ArgumentParser(fromfile_prefix_chars="@", description="""
        Compile the specified checkers, or every file in the working directory
    """)
    parser.add_argument("-f", "--force", action="store_true", help="""
        rebuild even if up-to-date
    """)
    parser.add_argument("-o", "--output-dir", default="bin", help="""
        directory to place the binaries in (default: %(default)s)
    """)
    parser.add_argument("source", nargs="*", help="""
        files to be compiled
    """)

    args = parser.parse_args()

    with contextlib.suppress(FileExistsError):
        os.mkdir(args.output_dir)

    if args.source:
        sources = args.source
        quiet = False
    else:
        sources = os.listdir()
        quiet = True

    success = True
    for filename in sources:
        success = process(filename, args.output_dir, args.force, quiet) and success

    sys.exit(not success)

if __name__ == "__main__":
    main()
