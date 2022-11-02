
struct expression* new_lambda_expression(
	struct type* type,
	unsigned id,
	struct parameter_list* parameters,
	struct unresolved* captured,
	struct expression* body);
