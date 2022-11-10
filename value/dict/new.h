
struct dict_value;
struct type;
struct value_dict;

struct value* new_dict_value(
	struct type* type);
	
struct value* new_dict_value_from_concat(
	struct type* type,
	struct dict_value* a,
	struct dict_value* b);
