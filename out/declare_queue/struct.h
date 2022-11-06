
struct declare_queue
{
	struct quack* todo;
	
	struct stringset* queued;
	struct stringset* done;
	
	struct stringtree* init_text;
	struct stringtree* assign_text;
	struct stringtree* uninit_text;
};

