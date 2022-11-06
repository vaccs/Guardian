
struct string_list;

void string_list_foreach(
	struct string_list* this,
	void (*runme)(struct string*));
