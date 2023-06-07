

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

with open("/tmp/json.guard", "w") as stream: stream.write("""

%skip: ' ' | '\\n';

string: /'\\"' [!'\\"']* '\\"'/ #value;

list: '[' (value #elements[] (',' value #elements[])*)? ']';

keyvalue: string #key ':' value #value;

dict: '{' (keyvalue #entries[] (',' keyvalue #entries[])*)? '}';

value
	: /bool: "true" | "false"/ #boolean
	| /int: ['-', '+']? ['0'-'9']+/ #integer
	| /float: ['-', '+']? ['0'-'9']+ '.' ['0'-'9']+/ #decimal
	| string #string
	| list #list
	| dict #dict
	;

start: value #value;

%parse: argv as start;

%error: start[0].value has list;

x = start[0].value.list.elements;

%error: len!(x) == 3;

%error: x[0] has boolean;
%error: x[0].boolean == true;

%error: x[1] has integer;
%error: x[1].integer == 2;

%error: x[2] has decimal;
%error: x[2].decimal == 3.4;

""");

executable = argv[1];

run([executable, "-i", "/tmp/json.guard", "-o", "/tmp/json.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/json.c", "-o", "/tmp/json", "-lgmp", "-lquadmath"]);

with open("/tmp/json.txt", "w") as stream: stream.write("""
  [true, 2, 3.4]
""");

run(["/tmp/json", "/tmp/json.txt"]);



























