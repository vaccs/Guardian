#!/usr/bin/python3

import subprocess;
from glob import glob;
from pathlib import Path
from os.path import getmtime;

executable = "./bin/test-build/yes-verbose/no-dotout/guardian";

for test in sorted(glob("tests/**/*.py", recursive = True), key = getmtime, reverse = True):
  print("\033[32m" f"running {test} ... " "\033[0m");
  result = subprocess.run(["python3", test, executable]);
  if result.returncode:
    print("\033[31m" f"failed {test} !" "\033[0m");
    Path(test).touch()
    exit(1);







