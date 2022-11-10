
struct named_expression;
struct named_expression_list;

void named_expression_list_foreach(
	struct named_expression_list* this,
	void (*runme)(struct named_expression*));
