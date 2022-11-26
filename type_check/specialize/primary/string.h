
struct type_cache;
struct zebu_token;

struct expression* specialize_primary_string_expression(
	struct type_cache* tcache,
	struct zebu_token* string_literal);
