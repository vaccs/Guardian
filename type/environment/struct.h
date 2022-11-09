
#include "../struct.h"

struct environment_type
{
	struct type super;
	
	struct environment_type* prev;
	
	struct avl_tree_t* variables;
};

