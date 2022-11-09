
struct type_cache;
struct avl_tree_t;
struct type_check_scope;

struct type* determine_type_of_logical_and_expression(
	struct zebu_logical_and_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
