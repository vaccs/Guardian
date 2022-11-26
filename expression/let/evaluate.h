
struct scope;
struct expression;

struct value* let_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* outside);
