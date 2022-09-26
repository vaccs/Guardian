
struct unresolved_node
{
	struct string* name;
	struct ptrset* usages; // primary_expressions;
	
	unsigned refcount;
};


