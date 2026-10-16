#ifndef TYPE_H

# define TYPE_H

typedef enum e_cmd_type
{
	CMD = 1,
	PIPE = 2,
	FD = 4,
	RIN = 8,
	ROUT = 16,
	APP = 32,
	HDOC = 64,
	DELIM = 128,
	VAR = 256,
	UNDEF = 512,
}	t_type;

#endif
