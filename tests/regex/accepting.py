
from sys import argv;

import os;
import subprocess;

def run(command, expected_stdout = None):
  line = ' '.join(command);
  print("\033[33m" + line + "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode:
    print("\033[31m subcommand failed!");
    exit(1);
  elif expected_stdout is not None and result.stdout != expected_stdout:
    print("\033[31m output does not match expectations!");
    exit(1);

with open("/tmp/test.guard", "w") as stream: stream.write("""

float:
     / ['0'-'9']+                 ['E', 'e'] ['+', '-']? ['0'-'9']+   ('f'|'F'|'l'|'L')?
     | ['0'-'9']* "." ['0'-'9']+ (['E', 'e'] ['+', '-']? ['0'-'9']+)? ('f'|'F'|'l'|'L')?
     | ['0'-'9']+ "." ['0'-'9']* (['E', 'e'] ['+', '-']? ['0'-'9']+)? ('f'|'F'|'l'|'L')? / ;

%parse: "/tmp/test.txt" as float;

""");

executable = argv[1];

run( \
  [executable, "-i", "/tmp/test.guard", "--print-shortest-accepting"], \
  expected_stdout = "%parse on line 8: \".0\"\n");

