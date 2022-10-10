
struct out_function
{
	struct ptrset* dependent_on; // struct out_function*
	struct ptrset* dependent_of; // struct out_function*
	
	struct stringtree* text;
	
	unsigned rank;
};

