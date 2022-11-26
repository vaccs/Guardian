
struct type_cache
{
	struct avl_tree_t* tree; // "owns" the types
	
	struct type* bool_type;
	
	struct type* int_type;
	
	struct type* float_type;
	
	struct type* string_type;
	
	unsigned next;
};
