
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

executable = argv[1];

with open("/tmp/range.guard", "w") as stream:
  stream.write("""
    %skip: ' ' | '\\n';

    integer: /int: ['0'-'9']+/ #value;

    %parse: argv as integer integer;

    t = range!(2, 6);
    
    %error: t == [2, 3, 4, 5];

    %error: ($int s, e -> int[]: range!(s, e))(3, 6) == [3, 4, 5];

    %error: range!(integer[0].value, integer[1].value) == [3, 4, 5];

    %error: range!(integer[1].value) == [0, 1, 2, 3, 4, 5];
""");

run([executable, "-i", "/tmp/range.guard", "-o", "/tmp/range.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/range.c", "-o", "/tmp/range", "-lgmp"]);

with open("/tmp/range.txt", "w") as stream:
  stream.write("""
    3 6
""");

run(["/tmp/range", "/tmp/range.txt"]);



































