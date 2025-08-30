#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

#include "get_next_line.h"

char *extract_new_line(char **string)
{
    char    *ptr_of_new_line;
    size_t  length_of_main_line;
    char *the_line;
    char *the_rest;
    char *old;

    if (!string || !*string)
        return (NULL);
    ptr_of_new_line = ft_gnl_strchr(*string, '\n');
    if (ptr_of_new_line)
    {
        length_of_main_line = (size_t)(ptr_of_new_line - *string + 1);
        the_line = ft_gnl_substr(*string, 0, length_of_main_line);
        the_rest = ft_gnl_substr(*string, length_of_main_line, ft_gnl_strlen(*string) - length_of_main_line);
        old = *string;
        *string = the_rest;
        free(old);
        return (the_line);
    }
    the_line = ft_gnl_substr(*string, 0, ft_gnl_strlen(*string));
    free(*string);
    *string = NULL;
    if (the_line && *the_line == '\0')
    {
        free(the_line);
        return (NULL);
    }
    return (the_line);

}

int read_until_next_line(int fd, char **string)
{
    char buf[BUFFER_SIZE + 1];
    ssize_t  read_bytes;

    while (!ft_gnl_strchr(*string, '\n'))
    {
        read_bytes = read(fd, buf, BUFFER_SIZE);
        if (read_bytes < 0)
            return (-1);
        if (read_bytes == 0)
            return (0);
        buf[read_bytes] = '\0';
        *string = ft_gnl_strjoin_free(*string, buf);
        if (!*string)
            return (-1);
    }
    return (1);
}
char	*get_next_line(int fd)
{
    static char *string;
    int  func_value;

    if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
    func_value = read_until_next_line(fd, &string);
    if (func_value == -1)
    {
        free(string);
        string = NULL;
        return (NULL);
    }
    return (extract_new_line(&string));
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
