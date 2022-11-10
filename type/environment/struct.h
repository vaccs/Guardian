
#include "../struct.h"

struct environment_type
{
	struct type super;
	
	struct type* prev;
	
	struct avl_tree_t* variables;
};

