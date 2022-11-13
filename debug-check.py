
import sys;

if len(sys.argv) != 2:
	print("need a file");
	exit(1);

with open(sys.argv[1]) as stream:
	stack = [];
	for line in stream:
		line = line[:-1];
		stripped = line.strip();
		if stripped and stripped[0] == '<':
			if stripped[1] != '/':
				stack.append(stripped[1:-1]);
				print(f"stack = {stack}")
			elif stack[-1] == stripped[2:-1]:
				stack.pop();
				print(f"stack = {stack}")
			else:
				print(f"error: unexpected '{line}'! expecting '</{stack[-1]}>'!");
				exit(1);
