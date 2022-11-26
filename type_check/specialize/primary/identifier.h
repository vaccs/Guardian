
struct type_cache;
struct type_check_scope;
struct zebu_primary_expression;

struct expression* specialize_primary_identifier_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression);
