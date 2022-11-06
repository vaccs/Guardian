
struct lex;
struct avl_tree_t;
struct raw_assertion_list;
struct type_cache;

void parse_driver(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct avl_tree_t* declares,
	struct raw_assertion_list* assertions,
	struct type_cache* tcache,
	const char* input_path);
