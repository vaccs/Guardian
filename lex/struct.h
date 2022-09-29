
struct lex
{
	struct avl_tree_t* token_to_id;
	struct avl_tree_t* id_to_token;
	
	struct avl_tree_t* tokenizer_cache;
	
	unsigned next_id, whitespace_token_id, EOF_token_id;
};

