
struct set_queue
{
	struct quack* todo;
	
	struct stringset* queued;
	
	struct stringtree* init_text;
	struct stringtree* uninit_text;
};

