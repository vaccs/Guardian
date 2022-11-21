
struct lex;
struct avl_tree_t;
struct statement_list;

void yacc(
	struct lex* lex,
	struct avl_tree_t* structinfos,
	struct avl_tree_t* grammar,
	struct statement_list* statements);
