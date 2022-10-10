
struct out_shared
{
	struct {
		struct quack* todo; // list of names
		struct stringset* queued;
	} sets, declares;
	
	struct function_lookup* flookup;
	
	struct type_lookup* tlookup;
};
