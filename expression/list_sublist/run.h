
struct type;
struct int_value;
struct list_value;

struct value* list_sublist_run(
	struct type* type,
	struct list_value* list,
	struct int_value* startindex,
	struct int_value*   endindex);
