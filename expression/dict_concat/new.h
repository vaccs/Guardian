
struct type_cache;

struct expression* new_dict_concat_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);
