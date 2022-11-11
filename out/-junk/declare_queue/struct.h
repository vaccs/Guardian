
struct declare_queue
{
	struct quack* todo;
	
	struct stringset* queued;
	struct stringset* done;
	
	struct stringtree* text;
};

