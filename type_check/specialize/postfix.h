
struct type_cache;
struct specialize_shared;

struct expression* specialize_postfix_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_postfix_expression* zexpression);
