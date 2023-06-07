
#ifndef ENUM_ERROR
#define ENUM_ERROR

enum error
{
	e_success,
	e_syscall_failed,
	e_syntax_error,
	e_bad_input_file,
	e_shift_reduce_error,
	e_reduce_reduce_error,
	e_out_of_memory,
};

#endif
