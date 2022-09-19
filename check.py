#! 
with open("/tmp/stdout") as stream:
	stack = [];
	for line in stream:
		line = line.strip();
		print(stack);
		print(line);
		if (line[0] == "<"):
			line = line[1:];
			if (line[0] == "/"):
				line = line[1:];
				name = line[:line.index(">")];
				if stack[-1] != name:
					assert(not "TODO");
				else:
					stack.pop();
			else:
				name = line[:line.index(">")];
				stack.append(name);

