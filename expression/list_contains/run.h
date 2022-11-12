
struct type;
struct value;
struct list_value;

struct value* list_contains_run(
	struct type* type,
	struct value* element,
	struct list_value* list);
