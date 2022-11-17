
struct raw_statement_list;
struct statement_list;

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types, // named types
	struct raw_statement_list* raw_statements,
	struct statement_list* statements);
