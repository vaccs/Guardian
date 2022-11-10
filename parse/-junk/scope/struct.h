


struct scope
{
	struct avl_tree_t* named_grammar;
	
	struct avl_tree_t* named_types; // only grammar rule types
	
	struct avl_tree_t* named_expressions;
	
	struct layer {
		
		// an initial layer should be pushed, declaring the builtins
		
		struct avl_tree_t* variables;
		
		// when you read a variable, first you look it up in the variable layers
		// then check the grammar names
		
		struct layer* prev;
	}* head;
};

