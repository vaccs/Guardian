
struct zebu_inclusion_expression;
struct specialize_shared;
struct type_check_scope;

struct expression* specialize_inclusion_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_inclusion_expression* zexpression);
