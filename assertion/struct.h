
#include <enums/assertion_kind.h>

struct assertion
{
	enum assertion_kind kind;
	
	struct expression* expression;
	
	unsigned refcount;
};

