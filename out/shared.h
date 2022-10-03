
struct out_shared
{
	struct {
		struct quack* todo; // `struct type*`
		struct avl_tree_t* queued;
	} lambda, compare, index, new, free, inc;
	
	struct {
		struct quack* todo;
		struct avl_tree_t* lookup;
		unsigned next;
	} type;
};

