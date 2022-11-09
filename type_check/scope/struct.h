
struct type_check_scope_layer;

struct type_check_scope
{
	struct avl_tree_t* grammar_types; // named type, do not free
	
	struct type_check_scope_layer* head;
};

