
struct raw_statement_list;
struct raw_declaration_list;
struct lex;
struct avl_tree_t;
struct raw_assertion_list;
struct type_cache;

void parse_driver(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct raw_statement_list* statements,
	const char* input_path);
