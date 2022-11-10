
struct type_cache;
struct avl_tree_t;

void specialize_grammar_types(
	struct avl_tree_t* types, // named_type*
	struct type_cache* tcache,
	struct avl_tree_t* structinfos); // named_structinfo*
