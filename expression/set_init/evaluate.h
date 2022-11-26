
struct expression;
struct scope;

struct value* set_init_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);
