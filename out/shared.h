
struct shared
{
	struct {
		struct quack* todo; // list of names
		struct stringset* queued;
	} set, declare;
	
	struct function_lookup* flookup;
	
	struct type_lookup* tlookup;
};
