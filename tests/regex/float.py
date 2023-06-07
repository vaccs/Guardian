
from sys import argv;

import os;
import subprocess;

def run(command, comment = ""):
  line = ' '.join(command);
  if comment:
    line += " # " + comment;
  print("\033[33m" + line + "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode:
    print("\033[31m subcommand failed!");
    exit(1);

with open("/tmp/float.guard", "w") as stream: stream.write("""

float:
     / ['0'-'9']+                 ['E', 'e'] ['+', '-']? ['0'-'9']+   ('f'|'F'|'l'|'L')?
     | ['0'-'9']* "." ['0'-'9']+ (['E', 'e'] ['+', '-']? ['0'-'9']+)? ('f'|'F'|'l'|'L')?
     | ['0'-'9']+ "." ['0'-'9']* (['E', 'e'] ['+', '-']? ['0'-'9']+)? ('f'|'F'|'l'|'L')? / ;

%parse: "/tmp/float.txt" as float;

""");

executable = argv[1];

run([executable, "-i", "/tmp/float.guard", "-o", "/tmp/float.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/float.c", "-o", "/tmp/float"]);

for text in ["3e+1f", ".14L", "1."]:
  with open("/tmp/float.txt", "w") as stream:
    stream.write(text);
  run(["/tmp/float"], comment = "on " + text);

