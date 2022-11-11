
struct type_check_scope;
struct type_cache;
struct specialize_shared;

struct expression* specialize_and_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_and_expression* zexpression);
