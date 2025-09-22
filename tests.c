#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include "get_next_line.h"

//Does your function still work if the BUFFER_SIZE value is 9999?
//If it is 1? 10000000? Do you know why?
// Possible file descriptors:
// 	* 0, standard input
// 	* 1, standard output
// 	* 2, standard error
// 	* files, pipes, sockets, special files (like devices)
// What is the max legal malloc? Do not malloc for more.
// Clean up makefile esp. $(NAME) and verify compilation without it


// When argc = 1, read from stdin
// When argc = 2, read from file name at argv[1]
// When argc = 3, read from filename at argv[1] and set BUFFER_SIZE to argv[2] 
// Use a function to loop through calls to get_next_line to get at least one successive line at the time

void	*__real_malloc(size_t size);
void	__real_free(void *ptr);

static int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		integer;
	int		minus;

	i = skip_whitespace(str);
	integer = 0;
	minus = 0;
	if (str[i])
	{
		if (str[i] == '-')
		{
			minus = 1;
			i++;
		}
		else if (str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			integer = integer * 10 + str[i] - '0';
			i++;
		}
		if (minus)
			integer *= -1;
	}
	return (integer);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/* count = backtrace(tracePtrs, 10);
	char** funcNames = backtrace_symbols(tracePtrs, count);
	int fd = open("filenames.txt", O_WRONLY);
	for (size_t i = 0; i < count; i++)
		dprintf(fd, "%s\n", funcNames[i]);
	close(fd);
	
	__builtin_frame_address

	dprintf(2, "gnl free 3\n");
 
 * __wrap_malloc - malloc wrapper function 
 */
void	*__wrap_malloc(size_t size)
{
	void	*ptr;
	// void *tracePtrs[10];
	// size_t count;

	// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
	if (rand() % 101)
		ptr = __real_malloc(size);
	else
		ptr = NULL;
	
	dprintf(2, "malloc(%zu) = %p\n\n", size, ptr);
	return (ptr);
}


/* 
 * __wrap_free - free wrapper function 
 */
void	__wrap_free(void *ptr)
{
	dprintf(2, "free(%p)\n\n", ptr);
	__real_free(ptr);
}

int	main(int argc, char *argv[])
{
	char	*buf;
	int		fd;
	size_t	len = 0;
	char	*input = NULL;

	buf = "0";
	fd = 0;
	if (argc == 2)
	{
		printf("argv: %s\n", argv[1]);
		if (ft_isalpha(argv[1][0]))
			fd = open(argv[1], O_RDONLY);
		else
			fd = atoi(argv[1]);
		printf("fd: %i\n", fd);
		while (getline(&input, &len, stdin) != -1)
        {
            buf = get_next_line(fd);
            if (!buf)
            {
				printf("returned: %s\n", buf);
                printf("tests.c: [EOF] or Error\n");
                break;
            }
			else
			{
	        	printf("tests.c: |%s|", buf);
				dprintf(2, "main free buf\n");
   	        	free(buf);
				buf = NULL;
			}
		}
			dprintf(2, "main free input\n");
        free(input);
        close(fd);

		printf("file descriptor: %i\n", fd);
	}
	return (0);
}
