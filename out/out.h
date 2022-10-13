
struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* forwards,
	struct avl_tree_t* declares,
	struct quack* assertions,
	struct yacc_state* yacc_start);
