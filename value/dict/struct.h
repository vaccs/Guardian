
#include "../struct.h"

struct dict_value
{
	struct value super;
	
	struct value_pair_list* elements;
};

