
struct type_cache;
struct type_check_scope;
struct avl_tree_t;

struct type* determine_type_of_multiplicative_expression(
	struct zebu_multiplicative_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
