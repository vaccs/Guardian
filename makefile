
CC = gcc

CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors

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

buildprefix = gen/$(buildtype)-build

default: $(buildprefix)/maia

ARGS += -v

ARGS += -i ./examples/password.maia

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

gen/srclist.mk: | gen/%/
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path '*/-*' | sort -Vr | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include gen/srclist.mk
endif

objs := $(patsubst %.c,$(buildprefix)/%.o,$(srcs))
objs := $(patsubst %.S,$(buildprefix)/%.o,$(objs))

deps := $(patsubst %.c,$(buildprefix)/%.d,$(srcs))
deps := $(patsubst %.S,$(buildprefix)/%.d,$(deps))

$(buildprefix)/%.o $(buildprefix)/%.d: %.c | $(buildprefix)/%/
	@ echo "compiling $<"
	@ $(CC) -c $(CPPFLAGS) $(CFLAGS) $< -MD -o $(buildprefix)/$*.o $(ON_ERROR)

$(buildprefix)/maia: $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps)
endif
















