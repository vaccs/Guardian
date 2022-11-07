
struct value_list;
struct value;

void value_list_foreach(
	struct value_list* this,
	void (*runme)(struct value*));
