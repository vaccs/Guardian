
struct environment_type;
struct type_check_scope_layer;
struct type_check_scope;
struct avl_tree_t;
struct type_cache;
struct type_list;
struct type;

struct type* type_cache_get_environment_type2(
	struct type_cache* this,
	struct type* prev,
	struct avl_tree_t* variables); // named types;
	
	
