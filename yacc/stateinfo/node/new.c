
#include <debug.h>

#include <memory/smalloc.h>

#include <set/unsigned/inc.h>

#include "struct.h"
#include "new.h"

struct stateinfo_node* new_stateinfo_node(
	struct trie* trie,
	struct unsignedset* tokens)
{
	ENTER;
	
	struct stateinfo_node* this = smalloc(sizeof(*this));
	
	this->trie = trie;
	
	this->tokens = inc_unsignedset(tokens);
	
	EXIT;
	return this;
}

