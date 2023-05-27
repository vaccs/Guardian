
from sys import argv;

import subprocess;

def run(command):
    print("\033[33m" f"  $ {' '.join(command)}" "\033[0m");
    result = subprocess.run(command);
    if result.returncode:
        print("\033[31m" "    subcommand failed!");
        exit(1);

with open("/tmp/math.guard", "w") as stream: stream.write("""
%skip: ' ' | '\n';

highest
	: /int: ['0'-'9']+/ #literal
	| '(' add #subexp ')'
	;

multiply
	: highest #base
	| multiply #sub "*" highest #mutme
	| multiply #sub "/" highest #divme
	;

add	: multiply #base
	| add #sub "+" multiply #addme
	| add #sub "-" multiply #subme
	;

start: add #add;

%parse: "/tmp/math.txt" as start;

evalhigh = $highest h -> int: h has literal ? h.literal : evaladd(h.subexp);

evalmult = $multiply m -> int:
	m has base
		? evalhigh(m.base)
		: (m has mutme
			? evalmult(m.sub) * evalhigh(m.mutme)
			: evalmult(m.sub) / evalhigh(m.divme));

evaladd = $add a -> int:
	a has base
		? evalmult(a.base)
		: (a has addme
			? evaladd(a.sub) + evalmult(a.addme)
			: evaladd(a.sub) - evalmult(a.subme));

result = evaladd(start[0].add);

%error: result == 23;
""");

executable = argv[1];

run([executable, "-i", "/tmp/math.guard", "-o", "/tmp/math.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/math.c", "-o", "/tmp/math", "-lgmp"]);

with open("/tmp/math.txt", "w") as stream: stream.write("3 + 4 * 5");

run(["/tmp/math"]);


































