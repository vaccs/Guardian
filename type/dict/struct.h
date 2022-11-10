
#include "../struct.h"

struct dict_type
{
	struct type super;
	
	struct type* key;
	
	struct type* value;
};

