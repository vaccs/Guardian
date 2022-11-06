
struct capture;
struct capture_list;

void capture_list_foreach(
	struct capture_list* this,
	void (*runme)(
		struct capture* capture));
