
#include "../struct.h"

struct grammar_type
{
	struct type super;
	
	struct string* name;
	
	struct parameter_list* fields;
};

