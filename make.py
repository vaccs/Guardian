#!/usr/bin/python3

import sys;
import subprocess;
import pickle;
import atexit;

from time import time;
from glob import glob;
from os import environ, makedirs;
from os.path import exists, getmtime;

from heapq import heappush;
from heapq import heappop;

database = dict();

database_file = ".make.py.db";
if exists(database_file):
	with open(database_file, "rb") as stream:
		database = pickle.load(stream);

if "fail-times" not in database:
	database["fail-times"] = dict();

if "prev-commands" not in database:
	database["prev-commands"] = dict();

def flush_database():
	with open(database_file, "wb") as stream:
		pickle.dump(database, stream);

atexit.register(flush_database);

class recipe_object:
	def __init__(self, target):
		self.target = target;
		self.message = None;
		self.command = None;
		self.order_only = set();
		self.dep_on = set();
		self.dep_of = set();
		self.ftime = database["fail-times"].setdefault(target, time());
		self.waiting = 0;
	
	def add_dep(self, other, order_only = False):
		if order_only:
			self.order_only.add(other);
		else:
			self.dep_on.add(other);
		other.dep_of.add(self);
	
	def should_rebuild(self):
		if not exists(self.target):
			return True;
		
		if self.command != database["prev-commands"].get(self.target):
			return True;
		
		mtime = getmtime(self.target);
		return any(getmtime(dep.target) > mtime for dep in self.dep_on);
		
	def __lt__(self, other):
		return (self.ftime, self.target) > (other.ftime, other.target);
	
all_recipes = dict();

def recipe(name):
	if name not in all_recipes:
		x = recipe_object(name);
		all_recipes[name] = x;
	return all_recipes[name];

def make(start_targets):
	# update priorities:
	todo = set(all_recipes.values());
	while len(todo):
		element = todo.pop();
		for dep in element.dep_on:
			if dep.ftime < element.ftime:
				dep.ftime = element.ftime;
				todo.add(dep);
		for dep in element.order_only:
			if dep.ftime < element.ftime:
				dep.ftime = element.ftime;
				todo.add(dep);
	
	needed = set();
	
	# figure out which recipes are needed:
	todo = set([recipe(target) for target in start_targets])
	while len(todo):
		element = todo.pop();
		if element not in needed:
			needed.add(element);
			for dep in element.dep_on:
				todo.add(dep);
			for dep in element.order_only:
				todo.add(dep);
	
	todo = list();
	
	# add initial recipes to todo
	for element in needed:
		element.waiting = len(element.dep_on) + len(element.order_only);
		if element.waiting == 0:
			heappush(todo, element);
	
	# run commands, add more recipes to todo list, repeat as necessary:
	while len(todo):
		element = heappop(todo);
		
		if element.should_rebuild():
			if element.command is None:
			    print(f"no command to build '{element.target}'!");
			    print(f"(needed by {', '.join(d.target for d in element.dep_of)})");
			    exit(1);
			
			if (element.message is None):
			    print("\033[33m" f"$ {' '.join(element.command)}" "\033[0m");
			else:
			    print("\033[33m" f"{element.message}" "\033[0m");
			
			if '/' in element.target:
			    try:
			        makedirs(element.target[:element.target.rindex('/')]);
			    except FileExistsError:
			        pass
			
			result = subprocess.run(element.command);
			if result.returncode:
				print("\033[31m" f"subcommand failed for recipe {element.target}!");
				database["fail-times"][element.target] = time();
				exit(1);
			else:
				database["prev-commands"][element.target] = element.command;
		
		for dep in element.dep_of:
			dep.waiting -= 1;
			if dep.waiting == 0:
				heappush(todo, dep);
	

cc = "gcc";
cppflags = ["-D", "_GNU_SOURCE", "-I", "."];
cflags = ["-Wall", "-Werror", "-Wfatal-errors"];
ldflags = [];
ldlibs = ["-lgmp", "-lquadmath", "-lm"];

buildtype = environ.get("buildtype", "release");

if buildtype == "debug":
	cppflags += ["-D", "DEBUGGING"];
	
	cflags += ["-g"];
	cflags += ["-Wno-unused-variable"];
	cflags += ["-Wno-unused-but-set-variable"];
elif buildtype == "test":
	cppflags += ["-D", "TESTING"];
elif buildtype == "release":
	cppflags += ["-D", "RELEASE"];
	
	ldflags += ["-static"];
else:
	print("! UNKNOWN BUILD !");
	exit(1);

verbose = environ.get("verbose", "yes");

if verbose == "yes":
	cppflags += ["-D", "VERBOSE"];
elif buildtype == "no":
	pass;
else:
	print("! UNKNOWN VERBOSE VALUE !");
	exit(1);

buildprefix = f"build/{buildtype}-type/{verbose}-verbose";

dependency_files = list();
objects = list();

recipe("bin/escape").add_dep(recipe("-escape.c"));
recipe("bin/escape").command = ["gcc", "-Wall", "-Werror", "./-escape.c", "-o", "bin/escape"];
recipe("bin/escape").message = "compiling ./out/-template.c";

recipe("out/escaped.c").add_dep(recipe("bin/escape"));
recipe("out/escaped.c").add_dep(recipe("out/-template.c"));
recipe("out/escaped.c").command = ["bin/escape", "out/-template.c", "-v", "template", "-o", "./out/escaped.c"];
recipe("out/escaped.c").message = "escaping ./out/-template.c";

for src in glob("**/*.c", recursive = True):
	if "-" not in src:
		obj = buildprefix + "/" + src[:-2] + ".o";
		dep = buildprefix + "/" + src[:-2] + ".d";
		
		command = [cc, "-c", *cppflags, *cflags, src, "-MMD", "-MF", dep, "-o", obj];
		message = f"compiling {src} ...";
		
		recipe(obj).add_dep(recipe(src));
		recipe(obj).command = command;
		recipe(obj).message = message;
		
		recipe(dep).add_dep(recipe(src));
		recipe(dep).command = command;
		recipe(dep).message = message;
		
		objects.append(obj);
		dependency_files.append(dep);
	
executable = buildprefix + "/" + "guardian";

for obj in objects: recipe(executable).add_dep(recipe(obj));
recipe(executable).command = [cc, *ldflags, *objects, *ldlibs, "-o", executable];
recipe(executable).message = f"linking {executable} ...";

args = [];

args += ["-v"];
#args += ["-m"];

#args += ["-i", "./examples/apache.guard"];
args += ["-i", "./examples/flat-odt.guard"];

args += ["-o", "/tmp/out.c"];

recipe("run").add_dep(recipe(executable));
recipe("run").command = [executable, *args];

recipe("valrun").add_dep(recipe(executable));
recipe("valrun").command = ["valgrind", "--", executable, *args];

# tests:

for src in glob("tests/**/*.py", recursive = True):
    
    test = buildprefix + "/" + src[:-3] + ".test";
    
    recipe(test).add_dep(recipe(src));
    recipe(test).add_dep(recipe(executable));
    
    if src.startswith("tests/flat-odt/"):
        recipe(test).add_dep(recipe("examples/flat-odt.guard"));
    
    recipe(test).message = f"running {src} test:";
    recipe(test).command = ["sh", "-c", f"python3 {src} {executable} && touch {test}"];
    
    recipe("test").add_dep(recipe(test));

recipe("test").message = f"all tests pass!";
recipe("test").command = ["touch", "test"];

# build and read the dependency files before considering the executable:
make(dependency_files);
for dependency_file in dependency_files:
    with open(dependency_file) as stream:
        target, *deps = stream.read().replace("\\\n", " ").split();
        target = target[:-1];
        for dep in deps: recipe(target).add_dep(recipe(dep));

if len(sys.argv) > 1:
	make(sys.argv[1:]);
else:
	make([executable]);






















