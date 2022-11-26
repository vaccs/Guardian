
struct type_cache;
struct specialize_shared;
struct type_check_scope;
struct zebu_primary_expression;

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression);
