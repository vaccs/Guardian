
#include "type.h"

struct structinfo_node
{
	enum structinfo_node_type type;
	
	struct string* name; // must be the first
	
	struct string* grammar; // might be NULL
	
	struct zebu_type* tokentype; // might be NULL
	
	unsigned refcount;
};

