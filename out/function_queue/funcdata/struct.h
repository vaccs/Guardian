
#include "kind.h"

struct funcdata
{
	enum funcdata_kind kind;
	
	struct type* type;
	
	struct lambda_expression* lexpression;
	
	unsigned id;
};

