
struct statement_list;
struct statement;

void statement_list_foreach(
	struct statement_list* this,
	void (*runme)(struct statement*));
