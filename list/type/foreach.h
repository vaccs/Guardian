
struct type;
struct type_list;

void type_list_foreach(
	struct type_list* this,
	void (*runme)(struct type*));
