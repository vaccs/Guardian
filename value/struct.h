
#ifndef STRUCT_VALUE
#define STRUCT_VALUE

#include "kind.h"

struct value
{
	enum value_kind kind;
	
	struct value_inheritance* inheritance;
	
	struct type* type;
	
	unsigned refcount;
};

#endif
