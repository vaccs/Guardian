
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

with open("/tmp/len.guard", "w") as stream:
  stream.write("""
    %skip: ' ' | '\\n';

    boolean: /bool: \"true\" | \"false\"/ #value;

    %parse: argv as boolean boolean;

    b = boolean[0].value;

    _ = len!([1, 2, 3]);

    %error: ($int[] x -> int: len!(x))([1, 2, 3]) == 3;

    %error: 3 == len!(\"abc\");

    %error: 3 == len!(b ? \"one\" : \"three\");

    %error: 3 == len!([1, 2, 3]);
    %error: 2 == len!([b, b]);

    %error: 2 == len!({0: 0, 1: 1});
    %error: 2 == len!({0: b, 1: b});

    %error: 2 == len!((0, 1));
    %error: 2 == len!((b, b));

    %error: 1 == len!({2, 2});
    %error: 2 == len!({2, 3});
    %error: 1 == len!({b, b});
""");

run([executable, "-i", "/tmp/len.guard", "-o", "/tmp/len.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/len.c", "-o", "/tmp/len", "-lgmp"]);

with open("/tmp/len.txt", "w") as stream:
  stream.write("""
    true false
""");

run(["/tmp/len", "/tmp/len.txt"]);



































