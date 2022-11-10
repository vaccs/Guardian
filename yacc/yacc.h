
struct lex;
struct avl_tree_t;

struct yacc_state* yacc(
	struct lex* lex,
	struct avl_tree_t* structinfos,
	struct avl_tree_t* grammar);
