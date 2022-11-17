
struct statement_list;
struct declaration_list;
struct assertion_list;

struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct statement_list* statements,
	struct yacc_state* yacc_start);
