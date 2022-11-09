
struct type_check_scope;
struct type_cache;
struct avl_tree_t;
struct type_check_scope;

struct type* determine_type_of_unary_expression(
	struct zebu_unary_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
