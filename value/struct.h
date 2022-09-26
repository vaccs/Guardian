
#include "kind.h"

struct value
{
	enum value_kind kind;
	
	struct type* type;
	
	unsigned refcount;
};

