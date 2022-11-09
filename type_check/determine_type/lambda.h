
struct type_cache;
struct avl_tree_t;
struct type_check_scope;
struct zebu_lambda_expression;

struct type* determine_type_of_lambda_expression(
	struct zebu_lambda_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
