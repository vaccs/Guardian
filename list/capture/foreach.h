
struct capture;

void capture_list_foreach(
	struct capture_list* this,
	void (*runme)(
		struct capture* capture));
