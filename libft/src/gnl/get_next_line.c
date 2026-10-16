#include "get_next_line.h"

static char	*trim_buffer(char *buf)
{
	char		*line;
	ssize_t		buf_size;
	ssize_t		new_len;

	line = NULL;
	buf_size = gnl_strlen(buf);
	new_len = gnl_strchr(buf, '\n') + 1;
	gnl_memmove(buf, buf + new_len, buf_size - new_len);
	line = gnl_strjoin(line, buf);
	if (!*buf)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_gnl(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		buf_size;

	line = NULL;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (gnl_strchr(buf[fd], '\n') != -1)
		line = trim_buffer(buf[fd]);
	while (gnl_strchr(buf[fd], '\n') == -1)
	{
		gnl_bzero(buf[fd], BUFFER_SIZE);
		buf_size = read(fd, buf[fd], BUFFER_SIZE);
		if (buf_size == -1)
		{
			gnl_bzero(buf[fd], BUFFER_SIZE);
			free(line);
			return (NULL);
		}
		if (buf_size == 0)
			return (line);
		line = gnl_strjoin(line, buf[fd]);
	}
	return (line);
}
