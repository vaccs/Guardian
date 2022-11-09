
struct avl_tree_t;
struct type_cache;
struct type_check_scope;

struct type* determine_type_of_and_expression(
	struct zebu_and_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
