
struct value_pair_list;
struct value_pair;

void value_pair_list_foreach(
	struct value_pair_list* this,
	void (*runme)(struct value_pair*));
