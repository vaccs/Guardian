
struct zebu_expression;
struct type_check_scope;
struct type_cache;

struct expression* specialize_primary_isexecutableby_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments, unsigned raw_len);
