
struct raw_statement_list;
struct raw_statement;

void raw_statement_list_foreach(
	struct raw_statement_list* this,
	void (*runme)(struct raw_statement*));
