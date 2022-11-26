
struct type_cache;
struct scope;
struct expression;

struct value* lambda_expression_evaluate(
	struct type_cache* tcache,
	struct expression* this,
	struct value* environment);
