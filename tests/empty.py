
from sys import argv;

import os;
import subprocess;

def run(command):
  print("\033[33m" f" $ {' '.join(command)}" "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode:
    print("\033[31m" " subcommand failed!");
    exit(1);

with open("/tmp/empty.guard", "w") as stream: stream.write("""
%note: 2 + 2 == 4;
""");

executable = argv[1];

run([executable, "-i", "/tmp/empty.guard", "-o", "/tmp/empty.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/empty.c", "-o", "/tmp/empty"]);

run(["/tmp/empty"]);

