
struct type_cache;
struct avl_tree_t;
struct zebu_implication_expression;
struct type_check_scope;

struct type* determine_type_of_implication_expression(
	struct zebu_implication_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
