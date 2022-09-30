
struct stringtree
{
	struct stringtree_node {
		bool is_branch;
		union {
			char* string;
			struct stringtree* subbranch;
		};
		struct stringtree_node* next;
	}* head, *tail;
};
