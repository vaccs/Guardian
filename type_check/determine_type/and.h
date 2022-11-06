
struct avl_tree_t;
struct type_cache;

struct type* determine_type_of_and_expression(
	struct zebu_and_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type);
