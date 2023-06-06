

from sys import argv;

import os;
import subprocess;

def run(command, exitcode = 0, expected_stderr = None):
  print("\033[33m" f" $ {' '.join(command)}" "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode != exitcode:
    print("\033[31m subcommand failed!");
    exit(1);
  elif expected_stderr is not None and result.stderr != expected_stderr:
    print("\033[31m output does not match expectations!");
    exit(1);

executable = argv[1];

run( \
  [executable, "-i", "/tmp/missing.guard", "-o", "/tmp/missing.c"], \
  expected_stderr = "guardian: open(\"missing.guard\"): No such file or directory\n", \
  exitcode = 1);

