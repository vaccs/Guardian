
struct type_check_scope_layer;

struct type_check_scope
{
	struct type_check_scope_layer* head;
	
	struct stringset* grammar_sets;
};

