
struct set_value;
struct dict_value;
struct type;
struct value;
struct list_value;

struct value* set_contains_run(
	struct type* type,
	struct value* element,
	struct set_value* set);
