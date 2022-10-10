
struct type_queue
{
	struct quack* todo;
	
	struct ptrset* queued;
	struct ptrset* done;
	
	struct stringtree* text;
};

