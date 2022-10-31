
struct zebu_expression;

struct expression* specialize_implication_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_expression* zexpression);
