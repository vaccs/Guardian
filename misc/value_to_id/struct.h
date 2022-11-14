

struct value_to_id_node
{
	struct value* value;
	unsigned id;
};

struct value_to_id
{
	struct avl_tree_t* tree;
	unsigned next_id;
};

