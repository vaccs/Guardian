
struct dict_value;
struct type;
struct value;
struct list_value;

struct value* dict_contains_run(
	struct type* type,
	struct value* element,
	struct dict_value* dict);
