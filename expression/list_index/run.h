
struct type;
struct int_value;
struct list_value;

struct value* list_index_run(
	struct type* type,
	struct list_value* list,
	struct int_value* index);
