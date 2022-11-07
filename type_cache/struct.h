
struct type_cache
{
	struct avl_tree_t* tree; // "owns" the types
	
	struct type* int_type;
	
	struct type* float_type;
	
	struct type* char_type;
	
	struct type* bool_type;
	
	struct type* charlist_type;
	
	unsigned next;
};
