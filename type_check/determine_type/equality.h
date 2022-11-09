
struct type_cache;
struct avl_tree_t;
struct type_check_scope;

struct type* determine_type_of_equality_expression(
	struct zebu_equality_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
