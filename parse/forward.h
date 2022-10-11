
struct zebu_forward_directive;

void process_forward(
	struct avl_tree_t* grammar,
	struct avl_tree_t* forwards,
	struct avl_tree_t* declares,
	struct zebu_forward_directive* forward);
