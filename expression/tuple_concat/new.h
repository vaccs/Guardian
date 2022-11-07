
struct type;

struct expression* new_tuple_concat_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);
