
struct avl_tree_t;
struct zebu_statement;
struct raw_statement_list;

void process_statement(
	struct avl_tree_t* grammar,
	struct raw_statement_list* statements,
	struct zebu_statement* statement);
