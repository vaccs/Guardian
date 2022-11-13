
struct subtype_queue
{
	struct {
		struct quack* todo;
		struct ptrset* queued;
		struct ptrset* done;
	} values, expressions;
	
	struct stringtree* text;
};

