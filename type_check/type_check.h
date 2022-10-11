
void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* typed_declares,
	struct quack* typed_assertions,
	struct avl_tree_t* raw_forwards,
	struct avl_tree_t* raw_declares,
	struct quack* raw_assertions);
