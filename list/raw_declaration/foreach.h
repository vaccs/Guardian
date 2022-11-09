
struct raw_declaration_list;
struct raw_declaration;

void raw_declaration_list_foreach(
	struct raw_declaration_list* this,
	void (*runme)(struct raw_declaration* this));
