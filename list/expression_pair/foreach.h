
struct expression_pair_list;
struct expression_pair;

void expression_pair_list_foreach(
	struct expression_pair_list* this,
	void (*runme)(struct expression_pair*));
