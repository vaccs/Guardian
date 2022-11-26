
struct type_cache;

struct type_check_scope;

struct zebu_expression;

struct expression* specialize_primary_map_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len);
