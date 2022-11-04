
CC = gcc

CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors

LDLIBS += -lgmp

buildtype ?= release

ifeq ($(buildtype), release)
CPPFLAGS += -D RELEASE

CFLAGS += -O2
CFLAGS += -flto

LDFLAGS += -flto=auto

else ifeq ($(buildtype), test)
CPPFLAGS += -D TESTING

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else ifeq ($(buildtype), debug)
CPPFLAGS += -D DEBUGGING
CPPFLAGS += -D ZEBU_DEBUG

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else
$(error "invalid buildtype!");
endif

on_error ?= do_nothing
ifeq ($(on_error), do_nothing)
ON_ERROR =
else ifeq ($(on_error), open_editor)
ON_ERROR += || ($$EDITOR $<; false)
else
$(error "invalid on_error option!");
endif

buildprefix = bin/$(buildtype)-build
depprefix   = dep/$(buildtype)-build

default: $(buildprefix)/maia

ARGS += -v

ARGS += -m
#ARGS += --minimize-lexer

#ARGS += -i ./examples/json.maia
#ARGS += -i ./examples/math.maia
ARGS += -i ./examples/zest.maia

ARGS += -o /tmp/out.c

run: $(buildprefix)/maia
	$< $(ARGS)

valrun: $(buildprefix)/maia
	valgrind $< $(ARGS)

valrun-stop: $(buildprefix)/maia
	valgrind --gen-suppressions=yes -- $< ${ARGS}

valrun-leak: $(buildprefix)/maia
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -- $< ${ARGS}

tracerun: $(buildprefix)/maia
	strace $< $(ARGS)

install: $(buildprefix)/maia
	@ mkdir -vp ~/bin/
	@ cp -vau $(buildprefix)/maia ~/bin/maia

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

$(buildprefix)/maia: $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps) dep/parse/parse.d
endif
















