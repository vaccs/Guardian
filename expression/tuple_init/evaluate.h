
struct scope;
struct expression;
struct type_cache;

struct value* tuple_init_expression_evaluate(
	struct type_cache* tcache,
	struct expression* this,
	struct value* environment);
