#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == 3)
			exit(0);
		if (fork() == 0)
		{
			while (1)
				;
		}
		i++;
	}
	while(1)
		;
}
