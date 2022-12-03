
CC = gcc

CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors

LDLIBS += -lgmp
LDLIBS += -lm

buildtype ?= release

ifeq ($(buildtype), release)
CPPFLAGS += -D RELEASE

CFLAGS += -O2
CFLAGS += -flto

LDFLAGS += -flto=auto
LDFLAGS += -static

else ifeq ($(buildtype), test)
CPPFLAGS += -D TESTING

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else ifeq ($(buildtype), debug)
CPPFLAGS += -D DEBUGGING
#CPPFLAGS += -D ZEBU_DEBUG

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

#CFLAGS += -fsanitize=address
#LDLIBS += -fsanitize=address -static-libasan

else
$(error "invalid buildtype!");
endif

verbose ?= yes
ifeq ($(verbose), yes)
CPPFLAGS += -D VERBOSE
else ifeq ($(verbose), no)
else
$(error "invalid verbose!");
endif

dotout ?= no
ifeq ($(dotout), yes)
CPPFLAGS += -D DOTOUT
else ifeq ($(dotout), no)
else
$(error "invalid dotout!");
endif

on_error ?= do_nothing
ifeq ($(on_error), do_nothing)
ON_ERROR =
else ifeq ($(on_error), open_editor)
ON_ERROR += || ($$EDITOR $<; false)
else
$(error "invalid on_error option!");
endif

buildprefix = bin/$(buildtype)-build/$(verbose)-verbose/$(dotout)-dotout
depprefix   = dep/$(buildtype)-build/$(verbose)-verbose/$(dotout)-dotout

default: $(buildprefix)/guardian

ARGS += -v

ARGS += -m

# ARGS += -i ./examples/json.guard
# ARGS += -i ./examples/math.guard
#ARGS += -i ./examples/passwd.guard
#ARGS += -i ./examples/shadow.guard
#ARGS += -i ./examples/group.guard
#ARGS += -i ./examples/login.guard
ARGS += -i ./examples/zest.guard

ARGS += -o /tmp/out.c

run: $(buildprefix)/guardian
	$< $(ARGS)

valrun: $(buildprefix)/guardian
	valgrind $< $(ARGS)

valrun-stop: $(buildprefix)/guardian
	valgrind --gen-suppressions=yes -- $< ${ARGS}

valrun-leak: $(buildprefix)/guardian
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 -- $< ${ARGS}

tracerun: $(buildprefix)/guardian
	strace $< $(ARGS)

install: $(buildprefix)/guardian
	@ mkdir -vp ~/bin/
	@ cp -vau $(buildprefix)/guardian ~/bin/guardian

.PRECIOUS: %/

%/:
	@ mkdir -p $@

srclist.mk:
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path '*/-*' | sort -V | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include srclist.mk
srcs += ./parse/parse.c
srcs += ./out/escaped.c
endif

objs := $(patsubst %.c,$(buildprefix)/%.o,$(srcs))
objs := $(patsubst %.S,$(buildprefix)/%.o,$(objs))

deps := $(patsubst %.c,$(depprefix)/%.d,$(srcs))
deps := $(patsubst %.S,$(depprefix)/%.d,$(deps))

bin/escape: ./-escape.c | bin/
	@ echo "compiling $<"
	@ gcc -Wall -Werror ./$< -o $@

./out/escaped.c: bin/escape ./out/-template.c
	@ echo "escaping $*"
	@ $^ -v template -o $@

parse/parse.c parse/parse.h dep/parse/parse.d: parse/parse.zb | dep/parse/
	zebu -v -m --template=fileio -i $< -o parse/parse -MF dep/parse/parse.d

$(buildprefix)/%.o $(depprefix)/%.d: %.c | $(buildprefix)/%/ $(depprefix)/%/
	@ echo "compiling $<"
	@ $(CC) -c $(CPPFLAGS) $(CFLAGS) $< -MMD -o $(buildprefix)/$*.o -MF $(depprefix)/$*.d $(ON_ERROR)

$(buildprefix)/guardian: $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps) dep/parse/parse.d
endif
















