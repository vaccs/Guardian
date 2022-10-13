
#include "type.h"

struct structinfo_node
{
	enum structinfo_node_type type;
	
	struct string* name; // must be the first
	
	struct string* grammar; // might be NULL
	
	char conversion_char; // might be NULL
	
	unsigned refcount;
};

