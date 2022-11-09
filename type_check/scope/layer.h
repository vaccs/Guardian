
#include <stdbool.h>

struct avl_tree_t;

struct type_check_scope_layer {
	struct avl_tree_t* tree; // type_check_scope_nodes
	
	bool is_pure;
	
	struct type_check_scope_layer* prev;
};
