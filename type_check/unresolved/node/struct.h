
struct unresolved_node
{
	struct string* name;
	
	struct {
		struct zpexpressionset *current;
		struct zpexpressionset *deeper;
	} layers;
	
	unsigned refcount;
};


