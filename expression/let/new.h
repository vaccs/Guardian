
struct type;
struct expression_list;
struct expression;

struct expression* new_let_expression(
	struct type* type,
	struct type* environment,
	struct named_expression_list* parameters,
	struct expression* body);
