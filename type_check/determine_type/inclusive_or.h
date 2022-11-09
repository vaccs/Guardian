
struct type_cache;
struct avl_tree_t;
struct type_check_scope;

struct type* determine_type_of_inclusive_or_expression(
	struct zebu_inclusive_or_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
