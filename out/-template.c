
#define _GNU_SOURCE

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <gmp.h>

#define argv0 (program_invocation_name)

// integers, booleans, lambdas, lists, tuples, ...
{{STRUCTS}}

// new()s, inc()s, free()s, compare()s, index()s, ...
{{FUNCTIONS}}

// parser-tables

int main(int argc, const char** argv)
{
	puts("hello, world!");
	
	// create sets:
	{{INIT_SETS}}
	
	// parsing, with reduction-rules that build parse-tree and sets
	
	// variable declarations:
	{{INIT_DECLARES}}
	
	// assertions:
	{{ASSERTIONS}}
	
	// clean up declarations:
	{{UNINIT_DECLARES}}
	
	// clean up sets:
	{{UNINIT_SETS}}
	
	return 0;
}

