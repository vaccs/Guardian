
struct lex;
struct zebu_entry;

void process_grammar(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct avl_tree_t* declares,
	struct type_cache* tcache,
	struct zebu_entry* entry);
	
void process_start(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct zebu_entry* entry);
