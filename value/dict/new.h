
struct value_pair_list;
struct dict_value;
struct type;
struct value_dict;

struct value* new_dict_value(
	struct type* type,
	struct value_pair_list* elements);
