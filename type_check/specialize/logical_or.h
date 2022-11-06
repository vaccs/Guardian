
struct type_cache;
struct specialize_shared;

struct expression* specialize_logical_or_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_logical_or_expression* zexpression);
