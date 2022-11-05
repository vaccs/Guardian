
#include "tree.h"
#include "node.h"

/* Insert a node before another node. Returns the new node.
 * If old is NULL, the item is appended to the tree.
 * O(lg n) */
extern avl_node_t *avl_insert_before(avl_tree_t *, avl_node_t *old, avl_node_t *new);

