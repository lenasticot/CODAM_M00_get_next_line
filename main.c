# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <stdlib.h>
# include <stdint.h>
#include "get_next_line.h"

int main(void)
{
	int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    get_next_line(-1);
    
    close(fd);
    return (0);
}
