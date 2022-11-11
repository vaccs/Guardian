
struct raw_declaration_list;
struct type_cache;
struct avl_tree_t;
struct stringset;
struct raw_assertion_list;
struct declaration_list;
struct assertion_list;

void type_check(
	struct type_cache* tcache,
	
	struct avl_tree_t* grammar_types, // named types
	
	struct raw_declaration_list* raw_declarations,
	struct raw_assertion_list* raw_assertions,
	
	struct declaration_list* declarations,
	struct assertion_list* assertions);
