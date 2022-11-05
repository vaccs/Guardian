
#include "tree.h"
#include "compare.h"
#include "freeitem.h"

/* Allocates and initializes a new tree for elements that will be
 * ordered using the supplied strcmp()-like function.
 * Returns NULL if memory could not be allocated.
 * O(1) */

avl_tree_t* avl_alloc_tree(
	avl_compare_t cmp,
	avl_freeitem_t freeitem);
