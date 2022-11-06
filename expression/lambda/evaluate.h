
struct scope;
struct expression;

struct value* lambda_expression_evaluate(
	struct expression* this,
	struct scope* scope);
