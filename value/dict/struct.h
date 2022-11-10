
#include "../struct.h"

struct dict_value
{
	struct value super;
	
	struct avl_tree_t* tree;
};

