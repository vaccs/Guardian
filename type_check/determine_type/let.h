
struct zebu_let_expression;
struct type_cache;
struct type_check_scope;

struct type* determine_type_of_let_expression(
	struct zebu_let_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);
