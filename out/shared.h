
struct out_shared
{
	struct type_cache* tcache;
	
	struct type_queue* tqueue;
	
	struct subtype_queue* stqueue;
	
	struct function_queue* fqueue;
	
	struct set_queue* squeue;
	
	struct declare_queue* dqueue;
};
