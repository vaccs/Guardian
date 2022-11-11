
struct type_check_scope;
struct specialize_shared;

struct expression* specialize_exponentiation_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_exponentiation_expression* zexpression);
