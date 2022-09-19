
#include "type.h"

struct structinfo_node
{
	struct string* name; // must be the first
	
	enum structinfo_node_type type;
	
	unsigned refcount;
};

