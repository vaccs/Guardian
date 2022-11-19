
#include <stdbool.h>

struct stringtree
{
	struct stringtree_node {
		enum {
			snk_cstring,
			snk_string,
			snk_subtree,
		} kind;
		union {
			char* cstring;
			struct string* string;
			struct stringtree* tree;
		};
		struct stringtree_node* next;
	}* head, *tail;
	
	unsigned refcount;
};
