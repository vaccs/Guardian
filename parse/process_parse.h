
struct lex;
struct avl_tree_t;
struct raw_statement_list;
struct zebu_parse_statement;

void process_parse(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct raw_statement_list* statements,
	struct zebu_parse_statement* zstatement);
