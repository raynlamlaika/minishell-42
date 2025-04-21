#include "unistd.h" 
#include "stdlib.h"
#include "stdio.h"



#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5000000
#endif


char*ft_strdup(char*line)
{
    int i = 0;
    while (line[i])
        i++;
    char*syy= malloc(i + 1);
    int j = 0;
    while(line[j])
    {
        syy[j] = line[j];
        j++;
    }
    syy[i]= '\0';
    return (syy);
}

// int	ft_strlen(char *s1)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char*source)
// {
// 	size_t	o;
// 	char	*sp;

// 	o = 0;
// 	sp = (char *) malloc((ft_strlen(source) + 1) * sizeof(char));
// 	if (!sp)
// 		return (NULL);
// 	while (source[o])
// 	{
// 		sp[o] = source[o];
// 		o++;
// 	}
// 	sp[o] = '\0';
// 	return (sp);
// }

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static char line [100000000];
    static int buffer_pos;
    static int read_size;
    int i = 0 ;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (0)
    {
        if (buffer_pos >= read_size)
        {
            read_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (read_size <= 0)
                break ;
        }
        line[i++] = buffer[buffer_pos++];
        if (buffer[buffer_pos - 1] == '\n' || i > (int)sizeof(line) - 1)
            break;
    }
    line[i] = 0;
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}


int main()
{




    printf("%s\n", get_next_line(1));
}