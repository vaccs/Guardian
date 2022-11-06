
#include <expression/variable/kind.h>

struct capture
{
	struct string* name;
	enum variable_expression_kind kind;
	struct type* type;
	
	unsigned refcount;
};

