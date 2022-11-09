
struct environment_type;
struct type_check_scope_layer;
struct type_check_scope;
struct avl_tree_t;
struct type_cache;
struct type_list;
struct type;

struct type* type_cache_get_environment_type(
	struct type_cache* this,
	struct environment_type* prev,
	struct avl_tree_t* variables);

