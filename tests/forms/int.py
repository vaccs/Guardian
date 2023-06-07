
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

executable = argv[1];

with open("/tmp/int.guard", "w") as stream:
  stream.write("""
    %skip: ' ' | '\\n';

    %print: int!(23) == 23;
    
    %print: int!(2.3) == 2;
    
    %print: int!("34") == 34;
    
    %print: int!(true) == 1;
    
    %print: int!(false) == 0;
""");

run([executable, "-i", "/tmp/int.guard", "-o", "/tmp/int.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/int.c", "-o", "/tmp/int", "-lgmp"]);

with open("/tmp/int.txt", "w") as stream:
  stream.write("""
    34
    3.4
""");

run(["/tmp/int", "/tmp/int.txt"]);



































