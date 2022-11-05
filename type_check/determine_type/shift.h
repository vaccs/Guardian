
struct type* determine_type_of_shift_expression(
	struct zebu_shift_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type);
