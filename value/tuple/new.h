
struct parameter_list;
struct scope;
struct expression;
struct value_list;

struct value* new_tuple_value(
	struct type* type,
	struct value_list* subvalues);
