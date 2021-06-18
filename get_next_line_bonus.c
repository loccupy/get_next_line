#include "get_next_line_bonus.h"
void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;

	str = (char *)b;
	while (len --)
		*str++ = (char)c;
	return (b);
}

int	ft_memdel(void **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

static char	*check_remainder(char *remainder, char **line)
{
	char	*p_n;

	p_n = NULL;
	if (remainder)
	{
		p_n = ft_strchr(remainder, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_n);
		}
		else
			*line = ft_strdup(remainder);
	}
	else
		*line = ft_strdup("");
	return (p_n);
}

static char	*touch_remainder(char *p_n, char **remainder)
{
	char	*tmp;

	if (p_n)
	{
		*p_n = '\0';
		tmp = *remainder;
		*remainder = ft_strdup(++p_n);
		if (tmp)
			free(tmp);
	}
	return (*remainder);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			byte_was_read;
	char		*p_n;
	static char	*remainder[FD_SIZE];

	byte_was_read = 1;
	if (!line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	p_n = check_remainder(remainder[fd], line);
	while (!p_n && byte_was_read)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		buf[byte_was_read] = '\0';
		p_n = ft_strchr(buf, '\n');
		remainder[fd] = touch_remainder(p_n, &remainder[fd]);
		*line = ft_strjoin(*line, buf);
	}
	if (byte_was_read == 0)
		return (0 * ft_memdel((void **) &remainder[fd]));
	return (1);
}
