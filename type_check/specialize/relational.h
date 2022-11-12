
struct zebu_relational_expression;
struct type_check_scope;
struct type_cache;
struct specialize_shared;

struct expression* specialize_relational_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_relational_expression* zexpression);
