
void parse_driver(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct avl_tree_t* declares,
	struct quack* assertions,
	struct type_cache* tcache,
	const char* input_path);
