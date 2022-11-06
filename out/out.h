
struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct stringset* grammar_sets,
	struct declaration_list* declarations,
	struct assertion_list* assertions,
	struct yacc_state* yacc_start);
