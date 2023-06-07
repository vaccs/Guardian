
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
    exit(1);

with open("/tmp/reducereduce.guard", "w") as stream: stream.write("""

a: "abc";

b: "abc";

root: a | b;

%parse: argv as root;
""");

executable = argv[1];

run( \
  [executable, "-i", "/tmp/reducereduce.guard", "-o", "/tmp/reducereduce.c"], \
  stderr = "guardian: reduce/reduce error between grammar rule a and b!\n",
  exitcode = 5);

