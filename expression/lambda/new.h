
struct expression* new_lambda_expression(
	struct type* type,
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body);
