
struct function_queue
{
	struct quack* todo;
	
	struct avl_tree_t* queued;
	struct avl_tree_t* done;
	
	unsigned next;
	
	struct stringtree* text;
};

