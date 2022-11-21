
#include "../struct.h"

struct declare_statement
{
	struct statement super;
	
	struct string* name;
	
	struct expression* expression;
};

