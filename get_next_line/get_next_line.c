#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

#include "get_next_line.h"

static char	*extract_line_and_update(char **stash_ptr)
{
	char	*stash = *stash_ptr;
	char	*newline;
	size_t	len_line;
	char	*line;
	char	*rest;

	if (!stash || !*stash)
		return NULL;
	newline = ft_gnl_strchr(stash, '\n');

	if (newline)
	{
		len_line = (size_t)(newline - stash) + 1;
		line = ft_gnl_substr(stash, 0, len_line);
		rest = ft_gnl_substr(stash, len_line, ft_gnl_strlen(stash) - len_line);
		free(stash);
		*stash_ptr = rest;
		return line;
	}
	line = ft_gnl_substr(stash, 0, ft_gnl_strlen(stash));
	free(stash);
	*stash_ptr = NULL;
	if (line && *line == '\0')
	{
		free(line);
		return NULL;
	}
	return line;
}

static int	read_until_newline(int fd, char **stash_ptr)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	br;

	while (!ft_gnl_strchr(*stash_ptr, '\n'))
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0) 
			return -1;
		if (br == 0)
			return 0;
		buffer[br] = '\0';
		*stash_ptr = ft_gnl_strjoin_free(*stash_ptr, buffer);
		if (!*stash_ptr)
			return -1; 
	}
	return 1;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	status = read_until_newline(fd, &stash);
	if (status == -1) 
	{
		free(stash);
		stash = NULL;
		return NULL;
	}
	return extract_line_and_update(&stash);
}



int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    close(fd);
    return 0;
}

