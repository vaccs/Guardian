
struct environment_value;
struct type;
struct parameter_list;
struct scope;
struct expression;
struct named_type_list;

struct value* new_lambda_value(
	struct type* type,
	struct named_type_list* parameters,
	struct value* environment,
	struct expression* body);



