
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

with open("/tmp/abc.guard", "w") as stream: stream.write("""
%parse: "/tmp/abc.txt" as "abc";
""");

executable = argv[1];

run([executable, "-i", "/tmp/abc.guard", "-o", "/tmp/abc.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/abc.c", "-o", "/tmp/abc"]);

with open("/tmp/abc.txt", "w") as stream: stream.write("abc");

run(["/tmp/abc"]);

