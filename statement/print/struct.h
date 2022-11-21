
#include "../struct.h"

struct print_statement
{
	struct statement super;
	
	struct expression* expression;
};

