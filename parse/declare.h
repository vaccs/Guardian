
struct raw_declaration_list;
struct avl_tree_t;
struct zebu_value_declare;

void process_declare(
	struct avl_tree_t* grammar,
	struct raw_declaration_list* declarations,
	struct zebu_value_declare* declare);
