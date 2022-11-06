
struct type_cache;
struct avl_tree_t;

struct type* determine_type_of_exclusive_or_expression(
	struct zebu_exclusive_or_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type);
