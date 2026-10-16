#ifndef PRINTF_H
# define PRINTF_H

# ifndef BUF_SIZE
#  define BUF_SIZE 1024
# endif

# include <unistd.h>
# include "libstr.h"
# include <stdarg.h>

typedef struct s_buf
{
	char		arr[BUF_SIZE];
	int			size;
	int			len;
	int			fd;
}	t_buf;

enum e_type
{
	CHAR_TYPE,
	STR_TYPE,
	INT_TYPE,
	UINT_TYPE,
	LONG_UINT_TYPE,
	HEX_LOW_TYPE,
	HEX_UPP_TYPE
};

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_rprintf(int fd, const char *format, ...);

//UTILS

int	print_char(enum e_type type, va_list *args, int fd);
int	print_num(enum e_type type, va_list *args, int fd);
int	print_ptr(va_list *args, int fd);
int	print_hex(enum e_type type, va_list *args, int fd);

int	format_char(t_buf *buf, int c);
int	format_str(t_buf *buf, char *s);
int	format_ptr(t_buf *buf, void *ptr);
int	format_int(t_buf *buf, int n);
int	format_uint(t_buf *buf, unsigned int n);
int	format_uhex(t_buf *buf, unsigned int n);
int	format_lhex(t_buf *buf, unsigned int n);

int	flush_buffer(t_buf *buf);
int	buf_itoa(char *buf, int n);
int	buf_ultoa_base(char *buf, unsigned long n, char *base);

#endif
