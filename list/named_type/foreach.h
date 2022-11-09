
struct named_type;
struct named_type_list;

void named_type_list_foreach(
	struct named_type_list* this,
	void (*runme)(struct named_type*));
