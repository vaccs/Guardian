
struct avl_tree_t;
struct lex;
struct zebu_grammar_rule;

void process_grammar(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct avl_tree_t* declares,
	struct zebu_grammar_rule* rule);
