
#ifndef STRUCT_STATEMENT
#define STRUCT_STATEMENT

#include "kind.h"

struct statement
{
	enum statement_kind kind;
	
	struct statement_inheritance* inheritance;
	
	unsigned refcount;
	
	unsigned line;
};

#endif
