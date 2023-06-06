
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
    print(f"stdout: {result.stdout}");
    print(f"stderr: {result.stderr}");
    exit(1);

with open("/tmp/add.guard", "w") as stream: stream.write("""

integer: /int: ['0'-'9']+/ #value;

root: integer '+' integer;

%parse: "/tmp/3+4.txt" as root;

a = integer[0].value;
b = integer[1].value;

%error: 3 + 4 == 7;
%error: a + b == 7;

%error: {a, 1} + {b, 2} == {1, 2, a, b};

%error: [1, 2] + [3, 4] == [1, 2, 3, 4];
%error: [1, 2] + [a, b] == [1, 2, a, b];
""");

executable = argv[1];

run([executable, "-i", "/tmp/add.guard", "-o", "/tmp/add.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/add.c", "-o", "/tmp/add", "-lgmp"]);

with open("/tmp/3+4.txt", "w") as stream: stream.write("3+4");

run(["/tmp/add"]);

