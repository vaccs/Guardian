
struct declaration_list;
struct declaration;

void declaration_list_foreach(
	struct declaration_list* this,
	void (*runme)(struct declaration* this));
