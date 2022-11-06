
#ifndef STRUCT_ZEBU_ASSERTION
#define STRUCT_ZEBU_ASSERTION

#include <enums/assertion_kind.h>

struct raw_assertion
{
	enum assertion_kind kind;
	
	struct zebu_expression* expression; // owned. free when done.
	
	unsigned refcount;
};

#endif
