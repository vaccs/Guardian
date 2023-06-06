
from sys import argv;

import os;
import subprocess;

def run(command, stderr = None, exitcode = 0):
  print("\033[33m" f" $ {' '.join(command)}" "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode != exitcode:
    print("\033[31m" " subcommand failed!");
    exit(1);
  elif stderr is not None and result.stderr != stderr:
    print("output does not match expectations!");
    print(f"expecting: {stderr}");
    print(f"actual: {result.stderr}");
    exit(1);

with open("/tmp/shiftreduce.guard", "w") as stream: stream.write("""

b: "b" "c"?;

root: "a" b "c";

%parse: argv as root;
""");

executable = argv[1];

run( \
  [executable, "-i", "/tmp/shiftreduce.guard", "-o", "/tmp/shiftreduce.c"], \
  stderr = "guardian: shift/reduce error on token \"c\"\n",
  exitcode = 4);

