
struct declare_queue
{
	struct quack* todo;
	
	struct stringset* queued;
	struct stringset* done;
	
	struct stringtree* forward_text;
	struct stringtree* init_text;
	struct stringtree* uninit_text;
};

