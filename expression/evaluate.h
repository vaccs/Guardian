
struct expression;
struct scope;

struct value* expression_evaluate(
	struct expression* this,
	struct scope* scope);
