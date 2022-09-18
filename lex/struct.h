
struct lex
{
	struct avl_tree_t* token_to_id;
	
	unsigned next_id, whitespace_token_id;
};

