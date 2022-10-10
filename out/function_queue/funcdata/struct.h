
#include "kind.h"

struct funcdata
{
	enum funcdata_kind kind;
	
	struct type* type;
	
	unsigned id;
};

