
#include "../struct.h"

struct tuple_value
{
	struct value super;
	
	struct value_list* subvalues;
};

