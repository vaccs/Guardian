
#include "../struct.h"

struct environment_value
{
	struct value super;
	
	struct avl_tree_t* variables;
	
	struct value* prev;
};

