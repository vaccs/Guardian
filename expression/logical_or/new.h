
struct type;
struct type_cache;

struct expression* new_logical_or_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);
