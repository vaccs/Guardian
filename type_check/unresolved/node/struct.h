
struct unresolved_node
{
	struct string* name;
	
	struct {
		struct ptrset *current; // primary_expressions;
		struct ptrset *deeper; // primary_expressions;
	} layers;
	
	unsigned refcount;
};


