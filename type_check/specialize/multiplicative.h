
struct type_cache;
struct type_check_scope;
struct specialize_shared;

struct expression* specialize_multiplicative_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_multiplicative_expression* zexpression);
