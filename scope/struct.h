
struct scope
{
	struct avl_tree_t* tree;
	
	struct scope* prev;
	
	unsigned refcount;
};

