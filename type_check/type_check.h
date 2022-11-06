
struct stringset;
struct raw_assertion_list;
struct declaration_list;
struct assertion_list;

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types, // named types?
	
	struct avl_tree_t* raw_declares, // named_zebu_expression
	struct raw_assertion_list* raw_assertions, // ptrset of zebu_expressions?
	
	struct stringset* grammar_sets,
	struct declaration_list* declarations,
	struct assertion_list* assertions);
