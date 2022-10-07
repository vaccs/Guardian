
#ifndef STRUCT_TYPE
#define STRUCT_TYPE

#include "kind.h"

struct type
{
	enum type_kind kind;
	
	struct type_inheritance* inheritance;
	
	unsigned id;
	
	unsigned refcount;
};

#endif
