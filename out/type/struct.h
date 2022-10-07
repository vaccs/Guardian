
struct out_type
{
	struct ptrset* dependent_on; // struct out_type*
	struct ptrset* dependent_of; // struct out_type*
	
	struct stringtree* text;
	
	unsigned rank;
};

