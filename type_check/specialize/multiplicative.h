
struct type_check_scope;
struct specialize_shared;

struct expression* specialize_multiplicative_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_multiplicative_expression* zexpression);
