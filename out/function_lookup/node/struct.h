
#include "kind.h"

struct function_lookup_node
{
	enum function_lookup_node_kind kind;
	struct type* type;
	
	unsigned id;
	struct out_function* function;
};

