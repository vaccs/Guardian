
struct expression_list;
struct expression;

void expression_list_foreach(
	struct expression_list* this,
	void (*runme)(struct expression*));
