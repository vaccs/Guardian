
#include "../struct.h"

struct grammar_type
{
	struct type super;
	
	struct string* name;
	
	struct named_type_list* fields;
};

