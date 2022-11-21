
struct lex;
struct avl_tree_t;
struct zebu_start_directive;

void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct zebu_start_directive* entry);
