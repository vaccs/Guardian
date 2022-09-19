
#include "type.h"

struct structinfo_node
{
	struct string* name; // must be the first
	
	struct string* grammar; // might be NULL
	
	enum structinfo_node_type type;
	
	unsigned refcount;
};

