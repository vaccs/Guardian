
struct type_cache;

struct zebu_token;

struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer);
