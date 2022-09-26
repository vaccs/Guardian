
struct avl_tree_t;

void type_check(
	struct type_cache* tcache,
	struct avl_tree_t* types,
	struct avl_tree_t* typed_declares,
	struct ptrset* typed_assertions,
	struct avl_tree_t* raw_declares,
	struct ptrset* raw_assertions);



