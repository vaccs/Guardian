
#ifndef STRUCT_EXPRESSION
#define STRUCT_EXPRESSION

#include "kind.h"

struct expression
{
	enum expression_kind kind;
	struct expression_inheritance* inheritance;
	struct type* type;
	unsigned refcount;
};

#endif
