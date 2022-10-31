
struct expression* new_lambda_expression(
	struct type* type,
	unsigned id,
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body);
