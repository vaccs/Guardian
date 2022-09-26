
struct lex;
struct avl_tree_t;
struct zebu_start_directive;

void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct zebu_start_directive* entry);
