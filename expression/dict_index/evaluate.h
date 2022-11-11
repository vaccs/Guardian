
struct expression;
struct scope;

struct value* dict_index_expression_evaluate(
	struct expression* super,
	struct scope* scope);
