
struct out_shared;
struct avl_tree_t;

void set_queue_process(
	struct set_queue* this,
	struct avl_tree_t* grammar_types,
	struct stringset* grammar_sets,
	struct out_shared* shared);
