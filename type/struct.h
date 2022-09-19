
#include "kind.h"

struct type
{
	enum type_kind kind;
	
	unsigned refcount;
};

